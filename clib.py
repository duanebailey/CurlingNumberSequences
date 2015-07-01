#Copyright (c) Adly Templeton 2015 All rights reserved
#Various functions for studying curling numbers
#Run python3 clib.py help for documentation
import sys
import random
import time
def bruteForceList(l):
    """Generates a list of all strings of list l"""
    if l == 1:
        return [[2], [3]]
    result = []
    prevIteration = bruteForceList(l-1)
    for string in prevIteration:
        #clone string
        l2 = list(string)
        l3 = list(string)
        
        l2.insert(0, 2)
        l3.insert(0, 3)

        result.append(l2)
        result.append(l3)
    return result
def bruteForceUpTo(l):
    result = []
    for i in range(1, l):
        result += bruteForceList(i)
    return result
def listFromInt(l, n):
    """Returns the sequence of length i of 2s and 3s which correspond bitwise to n"""
    result = []
    for i in range(l):
        result.append(3 if n & (1 << i) else 2) 
    return result
#Each 'node' is a list
#n[0] contains the data (either 2 or 3)
#Subsequent values link to the next nodes, if they exist
def bruteForceTree():
    """Unused helper function for a possibly more efficient version of back"""
    return [0, [2],[3]]
def selfrep(i):
    """Finds all strings s that contain themselves in their tail
    takes an integer i = the length to start at"""
    for s in bruteForceGen(i):
        t = tail(s)
        if l2s(t).count(l2s(s)) > 1:
            print(l2s(s) + " l: " + str(len(tail(s))) + " c: " + str(l2s(t).count(l2s(s))))
def selfrepl(i):
    """Version of selfrep that finds all srings with tails > 80"""
    for s in bruteForceGen(i):
        t = tail(s)
        if l2s(t).count(l2s(s)) > 1 and len(tail(s)) > 80:
            print(l2s(s) + " l: " + str(len(tail(s))) + " c: " + str(l2s(t).count(l2s(s))))
def expandTree(t, oldSize):
    """Unused helper function for a possibly more efficient version of back"""
    if oldSize == 1:
        t.append([2])
        t.append([3])
    else:
        #t[0] is reserved for data
        size = len(t) - 1

        for i in range(size):
            expandTree(t[i + 1], oldSize -1)
def treeToList(t):
    """Unused helper function for a possibly more efficient version of back"""
    size = len(t) - 1
    if size == 0:
        #Clone it
        return [list(t)]
    else:
        result = []
        for i in range(size):
            #Add the data of this branch to the result
            result += [[t[0]] + x for x in (treeToList(t[i+1]))]
        return result
def expand(s):
    while True:
        t = tail(s)
        yield t
        s = s + t[:len(t) - 1] + s
        print(len(s))
def expandFormat(s):
    i = 0
    for t in expand(s):
        i += 1
        count2 = len([x for x in t if x == 2])
        count3 = len([x for x in t if x == 3])
        print(str(i) + " | "+ str(len(t)) + " | " + str(count2/count3))
def flawlessGen(i = 1):
    for l in bruteForceGen(i):
        s = s2l(recur(l2s(l)))
        yield s
def bruteForceGen(i = 1):
    size = i
    while True:
        size += 1
        print(size)
        for result in bruteForceList(size):
            yield result
def sublists(s):
    for i in range(len(s)):
        yield s[i:]
def cn(s):
    kMax = 0
    for y in sublists(s):
        k = 0
        sCopy = list(s)
        while sCopy[len(sCopy) - len(y):] == y:
            k += 1
            sCopy = sCopy[:len(sCopy) -len(y)]
        if k > kMax:
            kMax = k
    return kMax
def cnLength(s):
    """Version of cn(s) that returns a tuple (cn(s), len(Y))"""
    kMax = 0
    ylen = 0
    for y in sublists(s):
        k = 0
        sCopy = list(s)
        while sCopy[len(sCopy) - len(y):] == y:
            k += 1
            sCopy = sCopy[:len(sCopy) -len(y)]
        if k > kMax:
            kMax = k
            yLen = len(y)
    return (kMax, yLen)
def tail(seq):
    #clone s
    s = list(seq)
    initialSize = len(s)
    i = -1
    while i != 1:
        i = cn(s)
        s.append(i)
    return(s[initialSize:])
def tailComplete(s):
    """returns s plus it's tail without line breaks"""
    return s + tail(s)
def rotten(s):
    """Returns 2 if s is 2-rotten, 3 if s is 3-rotten, 0 otherwise"""
    for prefix in [2, 3]:
        if len(tail(s)) > len(tail([prefix] + s)):
            return prefix
    return 0
def rottenInc(s):
    """Returns rotten(s) + s"""
    return [rotten(s)] + s
def rottenDiverge(s):
    """Returns the point where s diverges from it's rotten form"""
    t = tail(s)
    r = tail([rotten(s)] + s)
    for i in range(len(t)):
        if r[i] != t[i]:
            #Note that the output isn't zero-indexed
            return i + len(s) + 1
    return -1
def tailIntersperse(seq):
    """Version of tail that formats the output nicely in two ways
    First, it intersperses s with the tail, seperating each group with newlines
    Second, it offsets any instance of s in the tail with spaces"""
    #clone s
    print(l2s(seq))
    s = list(seq)
    initialSize = len(s)
    i = -1
    while i != 1:
        i = cn(s)
        s.append(i)
    search = l2s(seq)
    result = l2s(s[initialSize:])
    print(result.replace(search, " " + search + " "))

    print("\n")
def validBackward(test, s):
    """Returns true if the prefix test creates the tail s"""
    for i in range(len(s)):
        if cn(test + s[:i]) != s[i]:
            return False
    return True

def s2l(s):
    return [int(i) for i in s]

def l2s(l):
    return ''.join([str(x) for x in l])

def isWeak(s):
    return tail(s) == tail(s[1:])
def backFlawless(s):
    """Version of backMax that will append only strings made of A and B"""
    for test in flawlessGen():
        if validBackward(test, s) and not isWeak(test): 
            print(l2s(test))
def backMax(s):
    """Version of back that will continue, checking isWeak, trying to find the max starting sequence"""
    for test in bruteForceGen():
        if validBackward(test, s) and not isWeak(test): 
            print(l2s(test))
def backTot(s):
    """Version of backMax that will find s anywhere in the tail, not just the beginning"""
    for test in bruteForceGen():
        if l2s(s) in l2s(tail(test)):
            print(l2s(test))
def baselineNatural(n):
    """Returns a baseline number for the percentage given by natural(s)"""
    t = 0
    b = []
    s = 2 ** n
    if s > 600000:
        b = [listFromInt(n, random.randrange(s)) for x in range (600000)]
        s = len(b)
    else:
        b = bruteForceList(n)
    for l in b:
        t += natural(l)
    t /= s
    return t
def natural(s):
    """Returns the number of digits in s that are the natural curling number of the preceding sequence"""
    r = 0
    for i in range(1, len(s)):
        if cn(s[:i]) == s[i]:
            r += 1
    return r
def naturalVisual(s):
    """Returns a visual representation of the distribution of natural
    X represents natural digits, - represents non-natural"""
    print(l2s(s))
    #print(abstractVisual(l2s(s)))
    r = "-"
    for i in range(1, len(s)):
        r += "X" if cn(s[:i]) == s[i] else "-"
    return r
def tailLength(s):
    return(len(tail(s)))
def depend(s, line):
    """Prints a graphical representation of dependencies between the tail and the starting sequence
    A digit in the tail is considered to depend on a digit in the starting sequence directly
    if flipping the number in s causes a change in t, with all parts of the tail before t held constant"""
    sTail = tail(s)
    for i in range(len(sTail)):
        t = sTail[i]
        result = ""
        result += str(i)
        result += "("
        result += str(t)
        result += ")"
        
        #Pad the string
        result += (10 - len(result)) * ' '
        sCombined = list(s) + list(sTail[:i])
        for j in range(len(sCombined)):
            if j == line:
                result += "|"
            sClone = list(sCombined) 
            #Toggle the digit at sClone[j]
            sClone[j] = 3 if sClone[j] == 2 else 2
            
            result += "X" if (cn(sClone) != t) else "-"
        print(result)

def contS60(s):
    """Returns True if the tail of s contains S60"""
    return str(len(s)) + " - " + str(l2s(tail(s)).count("22232223223222322232322232223223222322232322232223223232223"))
def P234(s):
    """Determines if s fits properties P2, P3, P4"""
    #P2
    if s[0] != 2:
        return False
    #P3
    if "33" in l2s(s):
        return False
    #P4
    if "2222" in l2s(s):
        return False
    return True
def back(s):
    for test in bruteForceGen():
        if validBackward(test, s):
            return test
def abstractAB(s):
    r = ""
    while len(s) > 0:
        if s[:4] == "2232":
            r += "A"
            s = s[4:]
        elif s[:9] == "322232223":
            r += "B"
            s = s[9:]
        else:
            r += s[0]
            s = s[1:]
    return r
def abstract(s):
    r = ""
    while len(s) > 0:
        if s[:4] == "2232":
            r += "2"
            s = s[4:]
        elif s[:9] == "322232223":
            r += "3"
            s = s[9:]
        else:
            r += " <" + s[0] + "> "
            s = s[1:]
    return r
def recur(s):
    """Expands s using 2=2232 and 3 = 322232223"""
    result = ""
    for c in s:
        if c == '2':
            result += '2232'
        if c == '3':
            result += '322232223'
    return result
def abstractVisual(s):
    a = abstract(s)
    r = ""
    for c in a:
        r += c
        l = len(recur(c)) -1
        r += " " * l
    return r
def modRecur(s):
    """version of recur that attemps to get rid of single 2s"""
    s = recur(s)
    while s.find(recur("323")) != -1:
        #i represents position of 2232, so we need to skip past 322232223
        i = s.find(recur("323")) + 9
        s = s[:i] + "2232" + s[i:]
        #Find list before 323
        #Shift by 4 to offset the 2232 we just added
        i += 4
        l = s2l(s[:i])
        if cn(l) == 2:
            s = s[:i] + "2232" + s[i:]
    return s

def contRecur(s):
    """version of modrecur that continues more than once"""
    for i in range(int(input("Repetitions: "))):
        s = modRecur(s)
        print(s)
if __name__ == "__main__":
    prgm = sys.argv[1]
    while True:
        if prgm == "help":
            print("expand - infintely expands input (ie. 48e48)")
            print("selfrep - finds all self-replicating sequences above a length")
            print("selfreplong - selfrep but only gives sequences with tail above 80")
            print("cs59 - counts the number of times S59 appears in tail of input")
            print("tail - computes the tail of a sequence")
            print("taillen - length of tail")
            print("taili - version of tail with special formating")
            print("back - computes shortest sequence that produces a tail t")
            print("backmax - computes all sequences which satisfy back")
            print("backflawless - version of backmax that only looks at flawless prefixs")
            print("weak - determines if the sequence is weak")
            print("natural - returns the number of 'natural' digits in a sequence")
            print("natural-v - visualizes which digits satisfy natural")
            print("recur - expands a sequence using 2=2322 and 3 = 322232223")
            print("depend - graphic of which digits each digit in tail depends on")
            print("abstract - opposite of recur")
            print("modrecur - version of recur that replaces solo '2'")
            print("contrecur - modrecur repeated")
            print("rotten - determines if a sequence is rotten and returns the prefix that shortens it plus the original sequence")
            print("abstractab - Version of abstract with 'A' and 'B' instead of numbers")
            print("rottenDiv - determines the index of the place where the tail diverges from the rotten version of the tail")
            exit()
        data = input("")
        if prgm == "rottenDiv":
            print(rottenDiverge(s2l(data)))
        if prgm == "modrecur":
            print(modRecur(data))
        if prgm == "contrecur":
            contRecur(data)
        if prgm == "abstractab":
            print(abstractAB(data))
        if prgm == "abstract":
            print(abstract(data))
        if prgm == "expand":
            expandFormat(s2l(data))
        if prgm == "selfrep":
            selfrep(int(data))
        if prgm == "selfreplong":
            selfrepl(int(data))
        if prgm == "rotten":
            print(l2s(rottenInc(s2l(data))))
        if prgm == "cs59":
            print(contS60(s2l(data)))
        if data == 'out':
            prgm = input()
        #if prgm == 'inf':
        #    infExt(s2l(data))
        if prgm == 'taili':
            tailIntersperse(s2l(data))
        if prgm == 'tail':
            print(l2s(tail(s2l(data))))
        if prgm == "back":
           print(l2s(back(s2l(data))))
        if prgm == "backmax":
            backMax(s2l(data))
        if prgm == "backflawless":
            backFlawless(s2l(data))
        if prgm == "backtot":
            backTot(s2l(data))
        if prgm == "weak":
            print(isWeak(s2l(data)))
        if prgm == "natural":
            print(str(natural(s2l(data))) + "/" + str(len(data)))
        if prgm == "baseline":
            print(baselineNatural(int(data)))
        if prgm == "natural-v":
            print(naturalVisual(s2l(data)))
        if prgm == "taillen":
            print(tailLength(s2l(data)))
        if prgm == "recur":
            print(recur(data))
        if prgm == "depend":
            depend(s2l(data), int(input("Line break: ")))
