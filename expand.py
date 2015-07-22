"""Translates 1s and 3s, where each digit represents the number of 2s in between each 3, and 1=1332, into normal strings"""
while True:
    data = input()
    data = data.replace("1332", "1")
    #Note the careful ordering of replacements
    data = data.replace("3", "2223")
    data = data.replace("1", "2322232223223")
    data = "3" + data
    print(data)
