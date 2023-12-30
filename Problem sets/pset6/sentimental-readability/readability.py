string = input("Text: ")

letter_count = 0
word_count = 1
sentences_count = 0

sentences_ends_with = [".", "!", "?"]

for i in string:
    if i.isalpha():
        letter_count = letter_count + 1

    elif i == " ":
        word_count = word_count + 1

    elif i in sentences_ends_with:
        sentences_count = sentences_count + 1

l = (letter_count/word_count) * 100
s = (sentences_count/word_count) * 100

index = 0.0588 * l - 0.296 * s - 15.8

if index >= 16:
    print("Grade 16+")

elif index < 1:
    print("Before Grade 1")

else:
    print("Grade: ", round(index))