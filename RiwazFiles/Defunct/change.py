z = "Output.txt"
f = open(z, 'r')
u = f.readlines()

for x in u:
	s=""
	for a in x:
		if a == 'A': s=s+"223"
		elif a == '6': s=s+"232223"
		elif a == '7': s=s+"2232223"
		elif a=='4': s=s+"2223"
	print s
