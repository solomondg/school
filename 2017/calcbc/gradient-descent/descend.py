#!/usr/bin/env python3

import math
current = [3, 30]

def dx(n):
    x, y = n
    top = 7615*(x**2 + 1)*(7615*x + 13*y - 584) - x*abs(-7615*x - 13*y + 584)**2
    bottom = (x**2 + 1)**(3/2) * abs(-7615*x - 13*y + 584)

    return top/bottom


def dy(n):
    x, y = n
    top = 13 * (7615*x + 13*y - 584)
    bottom = math.sqrt(x**2 + 1) * abs(-7615*x - 13*y + 584)
    return top/bottom


def error(n):
    x, y = n
    top = abs(584 - 7615*x - 13*y)
    bottom = math.sqrt(x**2 + 1)
    return top/bottom

epsilon = [1e-7, 1e-4]

log = []

i = 0
for i in range(100000):
    current = [current[0] + -dx(current)*epsilon[0], current[1] + -dy(current)*epsilon[1]]
    #  print ("            ")
    #  print (i, end='\r')
    print(current, [-dx(current), -dy(current)])
    log.append([current[0], current[1], error(current)])
#
#  for i in range(1000000):
#      current = [current[0] + -dx(current)*epsilon[0], current[1] + -dy(current)*epsilon[1]]
#      #  print ("            ")
#      #  print (i, end='\r')
#      print(current)
#      log.append([current[0], current[1], error(current)])

print("\n")
csv = "a,b,c\n"
for x in log[::1000]:
    csv += str(x[0])
    csv += ','
    csv += str(x[1])
    csv += ','
    csv += str(x[2])
    csv += '\n'

with open('file2.csv', 'w') as f:
    f.write(csv)
