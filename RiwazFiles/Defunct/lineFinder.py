z = "data.txt"
f = open(z, 'r')
u = f.readlines()
maxLength = 0
maxCount = 0
count=1
for x in u:
	if len(x)>maxLength:
		maxLength = len(x)
		maxCount = count
	count=count+1
print maxLength, maxCount
