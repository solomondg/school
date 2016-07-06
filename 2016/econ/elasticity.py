p1 = 0
p2 = 0
q1 = 0
q2 = 0

q1 = float(input("Initial quantity demanded: "))
q2 = float(input("Changed quantity demanded: "))

p1 = float(input("Initial price: "))
p2 = float(input("Changed price: "))

pd = abs(p2 - p1)

qd = abs(q2 - q1)

quantity = qd / ((q1 + q2)/2)
price    = pd / ((p1 + p2)/2)

print (quantity / price)
