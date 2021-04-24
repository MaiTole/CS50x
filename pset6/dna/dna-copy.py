from sys import argv, exit
import csv
import re

if len(argv) != 3:
    print("Please provide 2 input files.")
    exit(1)

with open (argv[1], "r") as namelist:
    reader = csv.reader(namelist, delimiter=',')
    header = next(reader)
    headerNew = list(header)
    Seq1 = header[1]
    Seq2 = header[2]
    Seq3 = header[3]

with open (argv[2], "r") as dnaSequence:
    seqReader = csv.reader(dnaSequence, delimiter=',')
    dnaSeq = str(next(seqReader)[0])

##print(f"{dnaSeq}")
print(f"{Seq1}")

matches = re.finditer(Seq1, dnaSeq)
matches_positions = [match.start() for match in matches]
print(matches_positions)

matches2 = re.finditer(Seq2, dnaSeq)
matches2_positions = [match2.start() for match2 in matches2]
print(matches2_positions)

matches3 = re.finditer(Seq3, dnaSeq)
matches3_positions = [match3.start() for match3 in matches3]
print(matches3_positions)

def my_function(matches_positions, Seq1):
    count = 0
    countmax = 0
    for i in range(len(matches_positions)-1):
        if (matches_positions[i+1] - matches_positions[i]) == len(Seq1):
            count += 1
            if count > countmax:
                countmax = count
    return countmax+1

countSeq1 = my_function(matches_positions, Seq1)
countSeq2 = my_function(matches2_positions, Seq2)
countSeq3 = my_function(matches3_positions, Seq3)

print(countSeq1)
print(countSeq2)
print(countSeq3)

with open (argv[1], "r") as namelist:
    reader = csv.reader(namelist, delimiter=',')
    next(reader)
    for test in reader:
        if (int(test[1]) == countSeq1 and int(test[2]) == countSeq2 and int(test[3]) == countSeq3):
            print(test[0])
            exit(1)
    print("No match")


#########################################################################################################################################

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

##print(f"{dnaSeq}")
##print(f"{Seq1}")
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

##print(array)

with open (argv[1], "r") as namelist:
    reader = csv.reader(namelist, delimiter=',')
    next(reader)
    check = 0
    for test in reader:
        for i in range(1,len(headerNew)):
            if (int(test[i]) == array[i-1]):
                ##print(test[i])
                ##print(array[i-1])
                check += 1
            if check == (len(headerNew)-1):
                print(test[0])
                exit(1)
    print("No match")