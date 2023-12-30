from cs50 import SQL

database = SQL("sqlite:///fav.db")

lag = input("Witch language you want to count? ")

print(database.execute("SELECT COUNT(*) FROM fav WHERE language = ?", lag))