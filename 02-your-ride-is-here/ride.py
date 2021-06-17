"""
ID: caleb.h1
LANG: PYTHON3
PROG: ride
"""

with open('ride.in', 'r') as f:
    l1 = f.readline().strip()
    l2 = f.readline().strip()

t1 = t2 = 1
for c in l1:
    t1 *= ord(c) - 64

for c in l2:
    t2 *= ord(c) - 64

t1 %= 47
t2 %= 47

with open('ride.out', 'w') as f:
    if t1 == t2:
        f.writelines('GO\n')
    else:
        f.writelines('STAY\n')
