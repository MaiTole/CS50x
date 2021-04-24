import re
from cs50 import get_string

text = get_string("Text: ")

words = len(text.split())

sentences = len(re.split("\. |\? |\! ", text))

count = 0
for i in text:
    if i.isalpha() == True:
        count = count + 1
letters = count


grade = round(0.0588 * ((letters/words)*100) - 0.296 * ((sentences/words)*100) - 15.8)

if grade < 1:
    print("Before Grade 1")
elif grade > 15:
    print("Grade 16+")
else:
    print(f"Grade {grade}")