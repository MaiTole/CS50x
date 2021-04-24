from cs50 import get_int

while True:
  n = get_int("Height: ")
  if 1 <= n <= 8:
    break;

if (n == 1):
    print("#")
else:
  for i in range(2,n+1):
      print(" "*(n-i), "#"*(i-1))

  print("#"*i)