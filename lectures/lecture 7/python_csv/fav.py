import csv

fav = []

with open("fav.csv") as file:
    reader = csv.DictReader(file)
    for i in reader:
        fav.append(i)

language_count_dict = {}
problem_count_dict = {}

for i in fav:
    if problem_count_dict.get(i["problem"], None):
        problem_count_dict[i["problem"]] = problem_count_dict[i["problem"]] + 1

    else:
        problem_count_dict[i["problem"]] = 1


    if language_count_dict.get(i["language"], None):
        language_count_dict[i["language"]] = language_count_dict[i["language"]] + 1

    else:
        language_count_dict[i["language"]] = 1

sorted_lang = sorted(language_count_dict.items(), key=lambda x:x[1], reverse=True)
sorted_problem = sorted(problem_count_dict.items(), key=lambda x:x[1], reverse=True)

print(sorted_lang)
print(sorted_problem)
