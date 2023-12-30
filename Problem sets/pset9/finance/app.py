import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    #Getting the users stocks and cash  form Ddatabase
    try:
        portfolio = db.execute("SELECT * FROM portfolio WHERE id = ?", session["user_id"])
    except RuntimeError:
        portfolio = []

    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

    #Calculating total and adding current stock price to the portfolio
    final_total = 0
    for stock in portfolio:
        price = lookup(stock["symbol"])["price"]
        final_total = final_total + (price*stock["shares"])

        stock["price"] = usd(price)
        stock["total"] = usd(price * stock["shares"])

    final_total = final_total + cash

    #Removing all the symbol with 0 stocks
    for stock in portfolio:
        if stock["shares"] == 0:
            portfolio.remove(stock)

    return render_template("index.html", portfolio=portfolio, cash=usd(cash) , final_total=usd(final_total))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        symbol = request.form.get("symbol")
        ammount = request.form.get("shares")

        if not symbol or not ammount:
            return apology("Please fill out all required fields.", 400)

        if not ammount.isdigit():
            return apology("You cannot purchase partial shares.")

        ammount = int(ammount)

        if ammount <= 0:
            return apology("Can't but negetive number of shares", 400)

        share = lookup(symbol)

        if not share:
            return apology(f"{symbol} not found", 400)

        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

        if (user_cash - (share["price"]*ammount)) < 0:
            return apology("Insufficient funds", 400)

        date = str(datetime.datetime.now()).split(".")[0]

        db.execute("CREATE TABLE IF NOT EXISTS transactions (user_id INTEGER, date TEXT, symbol TEXT, shares INTEGER, price NUMERIC)")
        db.execute("INSERT INTO transactions (user_id, date, symbol, shares, price) VALUES (?, ?, ?, ?, ? )", session["user_id"], date, share["name"], ammount, share["price"])


        db.execute("CREATE TABLE IF NOT EXISTS portfolio (id INTEGER, symbol TEXT, shares INTEGER)")

        row = db.execute("SELECT * FROM portfolio WHERE id = ? AND symbol = ?", session["user_id"], share["symbol"])
        #Add new share
        if len(row) == 0:
            db.execute("INSERT INTO portfolio (id, symbol, shares) VALUES(?, ?, ?)", session["user_id"], share["symbol"], ammount)
        #Update existing ones
        else:
            new_ammount = db.execute("SELECT shares FROM portfolio WHERE id = ? AND symbol = ?", session["user_id"], share["symbol"])[0]["shares"] + ammount
            db.execute("UPDATE portfolio SET shares = ? WHERE id = ? AND symbol = ?", new_ammount, session["user_id"], share["symbol"])

        db.execute("UPDATE users SET cash = ? WHERE id = ?", ((user_cash - (share["price"]*ammount))), session["user_id"])

        return redirect("/")

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    try:
        row = db.execute("SELECT * FROM transactions WHERE user_id = ?", session["user_id"])
    except RuntimeError:
        return apology("You have not bought anything yet", 403)

    return render_template("history.html", history=row)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "POST":
        symbol = request.form.get("symbol")
        stock = lookup(symbol)

        if not stock:
            return apology(f"{symbol} not found.", 400)

        return_str = f"A share of {symbol} costs "
        price = usd(stock["price"])
        return render_template("quote.html", query=return_str, price=price)

    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        name = request.form.get("username")
        password = request.form.get("password")
        password_again = request.form.get("confirmation")

        if not name or not password or not password_again:
            return apology("Please fill out all required fields.", 400)

        if password != password_again:
            return apology("Confirmation password doesn't match", 400)

        rows = db.execute("SELECT * FROM users WHERE username = ?", name)
        if len(rows) > 0:
            return apology("Username taken", 400)

        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", name, generate_password_hash(password))
        return redirect("/")

    return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "POST":
        symbol = request.form.get("symbol")
        ammount = request.form.get("shares")

        if not symbol or not ammount:
            return apology("Please fill out all required fields.", 400)

        if not ammount.isdigit():
            return apology("You cannot sell partial shares.")

        ammount = int(ammount)

        if ammount <= 0:
            return apology("You cannot sell negetive or zero shares.")

        share = lookup(symbol)

        if not share:
            return apology(f"{symbol} not found")

        rows = db.execute("SELECT * FROM portfolio WHERE id = ? AND symbol = ?", session["user_id"], share["symbol"])

        if len(rows) == 0 or rows[0]["shares"] == 0:
            return apology(f"You dont have any shares from {symbol}", 400)

        if ammount > rows[0]["shares"]:
            return apology("You dont have enough shares to sell", 400)

        #Selling
        sold_for = share["price"] * ammount
        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
        db.execute("UPDATE users SET cash = ? WHERE id = ?", (sold_for + user_cash), session["user_id"])

        db.execute("UPDATE portfolio SET shares = ? WHERE id = ? AND symbol = ?", (rows[0]["shares"] - ammount), session["user_id"], share["symbol"])

        #Update history
        date = str(datetime.datetime.now()).split(".")[0]
        db.execute("INSERT INTO transactions (user_id, date, symbol, shares, price) VALUES (?, ?, ?, ?, ? )", session["user_id"], date, share["symbol"], ammount*(-1), share["price"])

        return redirect("/")

    portfolio = db.execute("SELECT * FROM portfolio WHERE id = ?", session["user_id"])

    if len(portfolio) == 0:
        portfolio = []

    return render_template("sell.html", portfolio=portfolio)

#personal touch
@app.route("/deposit", methods=["GET", "POST"])
@login_required
def deposit():
    if request.method == "POST":
        cash = float(request.form.get("cash"))

        if not cash:
            return apology("Please fill out all required fields.", 403)

        old_ammout = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash+old_ammout, session["user_id"])

        date = str(datetime.datetime.now()).split(".")[0]
        db.execute("INSERT INTO transactions (user_id, date, symbol, shares, price) VALUES (?, ?, ?, ?, ? )", session["user_id"], date, "deposit", 0, cash)

        return redirect("/")

    return render_template("deposit.html")


@app.route("/change_password", methods=["GET", "POST"])
@login_required
def change_password():
    if request.method == "POST":
        previous_password = request.form.get("previous_password")
        new_password = request.form.get("new_password")
        new_password_again = request.form.get("new_password_again")

        if not previous_password or not new_password or not new_password_again:
            return apology("Please fill out all required fields.", 403)

        if new_password != new_password_again:
            return apology("Confirm password doesn't match New password", 403)

        if not check_password_hash(db.execute("SELECT hash FROM users WHERE id = ?", session["user_id"])[0]["hash"], previous_password):
            return apology("incorrect password", 403)

        db.execute("UPDATE users SET hash = ? WHERE id = ?", generate_password_hash(new_password), session["user_id"])

        return redirect("/")

    return render_template("change_password.html")
