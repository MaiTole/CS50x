from cs50 import get_float

while True:
   changeOwed = get_float("Change owed: ")
   if changeOwed > 0:
    break

change = changeOwed * 100

coins25 = (change - (change % 25))/25
post25 = change - (coins25 * 25)

coins10 = (post25 - (post25 % 10))/10
post10 = post25 - (coins10 * 10)

coins5 = (post10 - (post10 % 5))/5
post5 = post10 - (coins5 * 5)

coins1 = (post5 - (post5 % 1))/1
post1 = post5 - (coins1 * 1)

coinstotal = coins25 + coins10 + coins5 + coins1

print(f"{coinstotal}")