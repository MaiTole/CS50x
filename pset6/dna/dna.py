from sys import argv, exit
import csv
import re

if len(argv) != 3:
    print("Please provide 2 input files.")
    exit(1)

with open (argv[2], "r") as dnaSequence:
    seqReader = csv.reader(dnaSequence, delimiter=',')
    dnaSeq = str(next(seqReader)[0])

with open (argv[1], "r") as namelist:
    reader = csv.reader(namelist, delimiter=',')
    header = next(reader)
    headerNew = list(header)
    for i in range(1, len(headerNew)):
      Seq = header[i]

def position_func(Seq, dnaSeq):
    matches = re.finditer(Seq, dnaSeq)
    matches_positions = [match.start() for match in matches]
    return matches_positions

def my_function(matches_positions, Seq):
    count = 0
    countmax = 0
    for i in range(len(matches_positions)-1):
        if (matches_positions[i+1] - matches_positions[i]) == len(Seq):
            count += 1
            if count > countmax:
                countmax = count
        else:
            count = 0
    return countmax+1

array = []
with open (argv[1], "r") as namelist:
    reader = csv.reader(namelist, delimiter=',')
    header = next(reader)
    headerNew = list(header)
    for i in range(1,len(headerNew)):
        Seq = header[i]
        countSeq = my_function(position_func(Seq, dnaSeq), Seq)
        array.append(countSeq)

with open (argv[1], "r") as namelist:
    reader = csv.reader(namelist, delimiter=',')
    next(reader)
    check = 0
    for test in reader:
        for i in range(1,len(headerNew)):
            if int(test[i]) == array[i-1]:
                check += 1
            else:
                check = 0
            if check == (len(headerNew)-1):
                print(test[0])
                exit(1)
    print("No match")