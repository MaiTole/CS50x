# TODO
import sys
from sys import argv, exit
import csv
from cs50 import SQL

db = SQL("sqlite:///students.db")
db.execute ("DELETE FROM students")
db.execute("CREATE TABLE IF NOT EXISTS students (first TEXT middle TEXT last TEXT house TEXT birth NUMERIC)")

if len(argv) != 2:
    print("CSV file not provided")
    exit(1)

with open (argv[1], "r") as characters:
    filereader = csv.DictReader(characters, delimiter=',')

    for row in filereader:
        housename = row["house"]
        birthyear = row["birth"]

        temp = row["name"].split()
        if len(temp) == 3:
            fname = temp[0]
            mname = temp[1]
            lname = temp[2]

        elif len(temp) == 2:
            fname = temp[0]
            mname = None
            lname = temp[1]
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", fname, mname, lname, housename, birthyear)


