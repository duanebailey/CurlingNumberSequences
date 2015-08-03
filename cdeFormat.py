"""Turns data into a string of CDE, then splits up the string of CDE based
 on occurances of DE/DCE. Data should be parsed
 (using python3 clib.py abstract) before being fed to this program

-m will read a sequence using the meta-language instead

(c) Adly Templeton 2015"""
data = input()
import sys


if len(sys.argv) > 1 and sys.argv[1] == '-m':
    data = data.replace("2", "")
    data = data.replace("3", "")

    #X is the error code - this allows multiple recursions of this program
    data = data.replace("X", "")
    
    #Use lowercase as a temp character
    data = data.replace("DCCECC", "c")
    data = data.replace("DECC", "d")
    data = data.replace("DCECC", "e")
    
    #Remove all digits that didn't get parsed and replace with X (error code)
    data = data.replace("C", "X")
    data = data.replace("D", "X")
    data = data.replace("E", "X")

    #Turn lowercase back into uppercase
    data = data.replace("c", "C")
    data = data.replace("d", "D")
    data = data.replace("e", "E")
else:
    #Note the ordering of these operations
    data = data.replace("222322232232223222323", "C")
    data = data.replace("22232232223222323", "E")
    data = data.replace("2232223222323", "D")
print(data)
