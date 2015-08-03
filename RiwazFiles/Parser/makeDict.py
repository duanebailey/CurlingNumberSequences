import sys
x = sys.argv[1]


lines = [line.rstrip('\n') for line in open(x)]
for a in lines:
    print "X:" + a
