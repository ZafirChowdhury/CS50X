import tournament
import csv
filename = "2018m.csv"

teams = []
with open(filename) as csvfile:
    reader = csv.DictReader(csvfile)
    for row in reader:
        row["rating"] = int(row["rating"])
        teams.append(row)

print(tournament.simulate_round(teams))