"""Takes a series of 2s and 3s and outputs the number of 2s between each three"""

data = input()
i=0
r=""
for c in data:
    if c == '2':
        i+=1
    if c == '3':
        r += str(i)
        i = 0
print(r)
