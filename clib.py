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
def bruteForcePrint(i):
    for l in bruteForceList(i):
        print(l2s(l))
def bruteForceUpTo(l):
    result = []
    for i in range(1, l):
        result += bruteForceList(i)
    return result
def infGen(i):
    """Generates, proceding backwards, terms from the sequence given by infinitely expanding A and B"""
    depth = i
    yield 2
    for i in range(100):
        #Exclude the final 2, as it was already created by the last instance of the loop
        l = [2, 2, 3]
        for i in range(depth):
            l = [[2, 2, 3, 2] if x == 2 else [3, 2, 2, 2, 3, 2, 2, 2, 3] for x in l]
            #Flatten the list
            l = [x for y in l for x in y]
        for c in reversed(l):
            yield c
        depth+=1
def candidates(i):
    """Searches for candidates for A-like and B-like strings"""
    for s in bruteForceGen(i):
        if s[0] == 2: #and s[-1] == 2:
            #2s on the end must add up to 3
            #if (s[1] == 2 and s[2] == 3 and s[-2] == 3) or (s[1] == 3 and s[-2] == 2 and s[-3] == 3):
            if cn(s) < 3 and not "33" in l2s(s):
                    #Check for naturally occuring
                if l2s(tail(s + s + [2]))[:len(s) - 1] == l2s(s)[1:]:
                    print("A-like: {}".format(l2s(s)))
                    
def backInf(s):
    """Version of back using the sequence generated by infGen"""
    #This is very cheap - take exponential digits at a time
    prefix = []
    gen = infGen(0)
    while True:
        #This increases by factors of two
        for i in range(len(prefix) + 1):
            prefix = [next(gen)] + prefix
        prefixTemp = list(prefix)
        print(l2s(prefixTemp))
        flawless = True
        for c in s[:]:
            if cn(prefixTemp) != c:
                flawless = False
                break
            prefixTemp += [c]
        print(len(prefix))
        if flawless:
            break
    return prefix
            
def inf(i):
    for c in infGen(i):
        print(c)
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
def isSelfRep(s):
    """Determines if a sequence is self replicating"""
    t = tail(s)
    return l2s(t).count(l2s(s)) > 1
        
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
def flawlessGen(i = 1, silent = False):
    for l in bruteForceGen(i, silent):
        s = s2l(recur(l2s(l)))
        yield s
def bruteForceGen(i = 1, silent = False):
    size = i
    while True:
        size += 1
        if not silent:
            print(size)
        for result in bruteForceList(size):
            yield result
def sublists(s):
    for i in range(len(s)):
        yield s[i:]
def findWords(s):
    """Find two words, like A and B, with which the entire string can be subdivided. Ignores error in the first 10 or last 10 digits."""
    c = 3
    results = []
    while True:
        c += 1
        print(c)
        possible = [l2s(x) for x in bruteForceUpTo(c)]
        for a in possible:
            for b in possible:
                #Note the break, not continue, here
                #This creates a 'triangular' iteration
                
                if a == b:
                    break
                #if len(a) == 1 or len(b) == 1:
                #    break
                valid = True
                sCpy = l2s(s)
                while len(sCpy) > 0:
                    if sCpy[:len(b)] == b:
                        sCpy = sCpy[len(b):]
                        continue
                    if sCpy[:len(a)] == a:
                        sCpy = sCpy[len(a):]
                        continue
                    diff = len(s) - len(sCpy)
                    sCpy = sCpy[1:]
                    if diff < 7 or diff > len(s) - 7:
                        valid = False
                        break
                if valid and len(a) + len(b) < len(s) and not (a, b) in results:
                    results.append((a,b))
                    print("{} : {}".format(a, b))
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
def doubleRotten(s):
    """Prints 'Double' if a sequence is double-rotten"""
    t = len(tail(s))
    if len(tail([2] + s)) < t and len(tail([3] + s)) < t:
        print("Double")
def rotten(s):
    """Returns 2 if s is 2-rotten, 3 if s is 3-rotten, 0 otherwise"""
    for prefix in [2, 3]:
        if len(tail(s)) > len(tail([prefix] + s)):
            return prefix
    return 0
def rottenDrasticFilter(s):
    """Re-prints all sequences where a prefix decreases the tail by more than sys.argv[2]"""
    offset = int(sys.argv[2])
    if rottenDiff(s) > offset:
        print(l2s(s))
def rottenDiff(s):
    shortened = [rotten(s)] + s
    return len(tail(s)) - len(tail(shortened))
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
def rottenDivergeRelative(s):
    """Version of rottenDiverge that doens't add on the length of the starting sequence"""
    t = tail(s)
    r = tail([rotten(s)] + s)
    for i in range(len(t)):
        if r[i] != t[i]:
            #Note that the output isn't zero-indexed
            return i + 1
def rottenDivFilter(s):
    """Re-prints those sequences where rottenDiverge %2 == 0 and %3 != 0"""
    n = rottenDivergeRelative(s)
    if n > 20 and  n < 51:
        print(l2s(s))

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
    sFiltered = s.replace(" ", "")
    return [int(i) for i in sFiltered]

def l2s(l):
    return ''.join([str(x) for x in l])
def repeats(s):
    """Return any sequence with length >= 8 characters, which appears in s more than once"""
    for i in range(16, len(s)):
        if s.count(s[:i]) > 1:
            return s[:i]
    return ""
    
def isWeak(s):
    return tail(s) == tail(s[1:])

def weakFilter(s):
    if not isWeak(s):
        print(l2s(s))
def isWeakFront(s):
    if s[-1] != cn(s[:-1]):
        print(l2s(s))

def backFlawless(s):
    """Version of backMax that will append only strings made of A and B"""
    for test in flawlessGen():
        if validBackward(test, s) and not isWeak(test): 
            print(l2s(test))
def backFlawlessLimit(s):
    """Combination of back and backFlawless - returns all results below length 16"""
    result = []
    for test in flawlessGen(0, True):
        if(validBackward(test, s) and not isWeak(test)):
            result.append(l2s(test))
        if len(abstract(l2s(test))) > 10:
            return result
def backLimit(s):
    result = []
    for test in bruteForceGen(0, True):
        if(validBackward(test, s) and not isWeak(test)):
            result.append(l2s(test))
        if len(l2s(test)) > 10:
            return result
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
    """Prints a graphical representation of dependencies between the digits sequence
    A digit is considered to depend on a digit directly
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
def BABsearch(i):
    """Outputs a list of flawless sequences which contain a complete BAB in their tail"""
    for s in flawlessGen(int(i)):
        t = tail(s)
        if recur("323") in t:
            print(s)
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
def recurFlexible(s, A, B):
    """Version of recur using user supplied values for A and B"""
    result = ""
    for c in s:
        if c == '2':
            result += A
        if c == '3':
            result += B
    return result
def abstractVisual(s):
    a = abstract(s)
    r = ""
    for c in a:
        r += c
        l = len(recur(c)) -1
        r += " " * l
    return r
def infExt(s):
    """Given a starting string s, it will repeatedly 'save' the tail from destruction by replacing the terminal '1' with a '2'"""
    max = 150
    while True:
        t = tail(s)
        s = s + t
        if s[-2] == 4:
            s[-2] = 3
            s.pop(-1)
        else:
            s[-1] = 2
        print(str(len(t)) + " : " + str(len(s)))
        if len(t) > max:
            max = len(t)
            print("Starting Sequence: {} - Tail {}".format(l2s(s), l2s(t)))
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
def analyze(s):
    """Runs a battery of tests and gives all possible information for s"""
    l = s2l(s)
    print("Analysis of sequence {}".format(s))
    print("Tail: {}".format(l2s(tail(l))))
    print("Tail length: {}".format(len(l2s(tail(l)))))
    print("The following sequences below length 11 produce this sequence as a tail: {}".format(backLimit(l)))
    print("The following sequences with an A-B length < 11 produce this sequence as a tail: {}".format(backFlawlessLimit(l)))
    print("This sequence is {} weak".format("" if isWeak(l) else "NOT"))
    print("Natural digits in this sequence: ")
    print(naturalVisual(l))
    print("Expansion of this sequence: {}".format(recur(s)))
    print("Abstraction of this sequence: {}".format(abstract(s)))
    print("Formatted abstraction:")
    print(s)
    print(abstractVisual(s))
    r = rotten(l)
    if r != 0:
        print("This sequence is {} rotten".format(r))
        print("The tail of the rotten sequence diverges from this sequence at digit {}".format(rottenDiverge(l)))
    else:
        print("This sequence is NOT rotten")
    repeat = repeats(s)
    if repeat != "":
        print("The string {} is repeated".format(repeat))
    print("This sequence is {} self replicating".format("" if isSelfRep(l) else "NOT"))
    print("Dependency matrix for the tail of this sequence:")
    depend(l, len(s))
    
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
            print("depend - graphic of which digits each digit in tail depends on.")
            print("abstract- opposite of recur")
            print("modrecur - version of recur that replaces solo '2'")
            print("contrecur - modrecur repeated")
            print("rotten - determines if a sequence is rotten and returns the prefix that shortens it")
            print("abstractab - Version of abstract with 'A' and 'B' instead of numbers")
            print("rottenDiv - determines the index of the place where the tail diverges from the rotten version of the tail")
            print("rottenDivRel - version of rottenDiv that will not add in the length of the starting sequence")
            print("repeats - prints an initial sequence that is repeated at least once in a string, if such a sequence exists")
            print("bab - searches for flawless sequences which contain BAB in their tail")
            print("double - prints 'double' if a sequence is rotten")
            print("inf - generates the infinite sequence backwards, starting at the middle")
            print("backinf - version of back using inf")
            print("findWords - will search a string for two words, such as A and B, which could make up the string recursively")
            print("candidates - will search for strings that match properties conjectured to be posessed by A-like and B-like strings")
            print("analyze - will run a battery of tests on a sequence and print the results")
            print("rottenDivFiler - filters out those sequences where rottenDiv % 2 == 0")
            print("weakFront - reprints the sequence if the last digit of the sequence does NOT follow naturally from the preceding")
            print("rottenDrasticFilter - filters out the rotten sequences where the reduction in length is greater than the second argument passed into the program")
            print("rottenDiff - returns the amount by which the tail of a rotten sequence is shortened")
            print("weakFilter - will only reprint input if the string is strong")
            print("all - will generate all sequences of a given length")
            print("infExt - will try to expand a starting sequence forever by saving it from destruction")
            exit()
        data = input("")
        if prgm == "infExt":
            infExt(s2l(data))
        if prgm == "all":
            bruteForcePrint(int(data))
        if prgm == "weakFilter":
            weakFilter(s2l(data))
        if prgm == "rottenDiff":
            print(rottenDiff(s2l(data)))
        if prgm == "rottenDrasticFilter":
            rottenDrasticFilter(s2l(data))
        if prgm == "weakFront":
            isWeakFront(s2l(data))
        if prgm == "rottenDivRel":
            print(rottenDivergeRelative(s2l(data)))
        if prgm == "rottenDivFilter":
            rottenDivFilter(s2l(data))
        if prgm == "analyze":
            analyze(data)
        if prgm == "findWords":
            findWords(s2l(data))
        if prgm == "candidates":
            candidates(int(data))
        if prgm == "backinf":
            print(l2s(backInf(s2l(data))))
        if prgm == "inf":
            inf(int(data))
        if prgm == "rottenDiv":
            print(rottenDiverge(s2l(data)))
        if prgm == "double":
            doubleRotten(s2l(data))
        if prgm == "modrecur":
            print(modRecur(data))
        if prgm == "repeats":
            r = repeats(data)
            if r != "":
                print(r)
        if prgm == "contrecur":
            contRecur(data)
        if prgm == "abstractab":
            print(abstractAB(data))
        if prgm == "abstract":
            print(abstract(data))
        if prgm == "bab":
            BABsearch(data)
        if prgm == "expand":
            expandFormat(s2l(data))
        if prgm == "selfrep":
            selfrep(int(data))
        if prgm == "selfreplong":
            selfrepl(int(data))
        if prgm == "rotten":
            print(rotten(s2l(data)))
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
