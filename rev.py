#!/usr/bin/env python3
from sys import stdin
for l in stdin:
    l = l.strip()
    if not l[0] == '*':
        continue
    l=l[1:]
    f = l.split(':')
    t = f[2].split()
    n = int(f[0])
    print('{:02}:'.format(n),end='')
    t = t[::-1]
    first=True
    while t:
        l = len(t)
        front = t[:25]
        t = t[25:]
        if not first:
            print('   ',end='')
        first=False
        for i in front:
            if l == n:
                print(':{}'.format(i),end='')
            else:
                print(' {}'.format(i),end='')
            l -= 1
        print()
