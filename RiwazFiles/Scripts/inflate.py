import sys
S = "A"
for x in range (0,6):
    d = ""
    for y in S:
        if y == "A":
            d+="AABA"
        else:
            d+="BAAABAAAB"
    S=d      
sys.stdout.write(S)  
