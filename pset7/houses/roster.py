# TODO
from sys import argv, exit
import csv
from cs50 import SQL

db = SQL("sqlite:///students.db")

if len(argv) != 2 :
    print("CSV file not provided")
    exit(1)

variableArg = argv[1]

myResult = db.execute("SELECT * FROM students WHERE house = (?) ORDER BY last ASC, first ASC", variableArg)
for result in myResult:
    if result["middle"] == None:
        print(result['first'] + ' ' + result['last'] + ', ' + 'born ' + str(result['birth']))
    else:
        print(result['first'] + ' ' + result['middle'] + ' ' + result['last'] + ', ' + 'born ' + str(result['birth']))