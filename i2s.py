from sys import stdin,argv
if len(argv)>1:
    w = int(argv[1])
    print("width {}".format(w))
else:
    w = 35

for line in stdin:
    s23=bin(int(line))[2:][::-1]
    l = len(s23)
    s=''
    for j in range(w):
        if j >= l:
            s += '2'
        else:
            s += '3' if s23[j] == '1' else '2'
    print(s)

