constant = 2**35
b=0
a = constant
for x in range(1,65):
	f = open("41 " + str(x), "w")
       	f.write("41\n" + str(b) + "\n" + str(a));
	b+=constant
	a+=constant
