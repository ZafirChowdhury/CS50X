from flask import Flask, render_template, request, redirect
from cs50 import SQL

app = Flask(__name__)

db = SQL("sqlite:///froshims.db")

SPORTS = [
    "Basketball",
    "Soccer",
    "Ultimate Frisbe"
]

@app.route("/")
def index():
    return render_template("index.html", sports=SPORTS)

@app.route("/register", methods=["POST"])
def register():
    name = request.form.get("user_name")
    if not name:
        return render_template("failed.html", return_text="Name missing")
    if request.form.get("sport") in SPORTS:
        sport = request.form.get("sport")
        db.execute("INSERT INTO registrants (name, sport) VALUES(?, ?)", name, sport)
        return redirect("registrants")
    else:
        return render_template("failed.html", return_text="Invalid Sport")

@app.route("/registrants", methods=["GET", "POST"])
def registrants():
    registrants = db.execute("SELECT * FROM registrants")
    return render_template("registrants.html", registrants=registrants)

@app.route("/deregister", methods=["POST"])
def deregister():
    id = request.form.get("id")
    if id:
        db.execute("DELETE FROM registrants WHERE id = ?", id)
    return redirect("/registrants")
