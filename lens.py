#!/usr/bin/env python3
# Compute ideal lengths of blocks.

def decode(n):
    if n == 1:
       return [1]
    elif n%2 == 0:
       m = (n-1)//3
       return [3]+decode(m)
    else:
       m = n-1
       if m%3 == 0:
         return [3]+decode(m//3)
       else:
         return [2]+decode(m//2)

l = [1]
def lens(n):
    if n == 1:
        return [[1]]
    else:
        tree = lens(n-1)
        layer = tree[0]
        next = []
        for i in layer:
            next.append(2*i+1)
            next.append(3*i+1)
        return [next]+tree


        
