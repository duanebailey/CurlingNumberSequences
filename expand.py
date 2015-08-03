"""Translates S and L, where each digit represents the number of 2s in between each 3, and S=3, L=1332, into normal strings"""
while True:
    data = input()
    #Note the careful ordering of replacements
    data = data.replace("S", "2223")
    data = data.replace("L", "2322232223223")
    data = "3" + data
    print(data)
