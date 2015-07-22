"""For a string of four digits, 0, 1, 2, 3, returns a matrix of how frequently 1 follows 2, etc"""

#matrix [1,2] represents the number of twos that follow a 1
matrix = [[0 for i in range(4)] for j in range(4)]

data = input()


#Word substitutions
data = data.replace("1332", "1")
print(data[:250])

for i in range(len(data) - 1):
    currentDigit = int(data[i])
    nextDigit = int(data[i + 1])
    matrix [currentDigit] [nextDigit] += 1
    #if i % 10000 == 0:
    #    print(i)
for i in [1, 3]:
    total = max(1, sum(matrix[i]))
    percent1 = (int)((100 * matrix[i][1]) / total)
    percent2 = (int)((100 * matrix[i][2]) / total)
    percent3 = (int)((100 * matrix[i][3]) / total)
    print("Digit {}: , {}% 1332, {}% 3, Total: {}".format(i, percent1, percent3, total))
