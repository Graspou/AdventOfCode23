l = []

with open('input/day3.txt', 'r') as f:
    for line in f:
        l.append(line)

symbols = '*'

def is_symbol_near_i(l, i, j):
    b = False
    pos = (0, 0)

    if i == 0 and j != 0 and j != len(l) - 1:
        conditions = [
            (l[i+1][j] == symbols, (i+1, j)),
            (l[i+1][j+1] == symbols, (i+1, j+1)),
            (l[i+1][j-1] == symbols, (i+1, j-1)),
            (l[i][j+1] == symbols, (i, j+1)),
            (l[i][j-1] == symbols, (i, j-1))
        ]

        for condition, position in conditions:
            if condition:
                b = True
                pos = position
                break

    elif i == len(l) - 1:
        conditions = [
            (l[i-1][j] == symbols, (i-1, j)),
            (l[i-1][j+1] == symbols, (i-1, j+1)),
            (l[i-1][j-1] == symbols, (i-1, j-1)),
            (l[i][j+1] == symbols, (i, j+1)),
             (l[i][j-1] == symbols, (i, j-1))
        ]

        for condition, position in conditions:
            if condition:
                b = True
                pos = position
                break
    elif j == len(l) -1:

    return b, pos

def is_symbol_near(l, i, j):
    if i == 0 or i == len(l) - 1 or j == 0 or j == len(l[0]) - 1:
        return is_symbol_near_i(l, i, j)

    conditions = [
        ((l[i][j+1] == symbols), (i, j+1)),
        ((l[i][j-1] == symbols), (i, j-1)),
        ((l[i+1][j] == symbols), (i+1, j)),
        ((l[i-1][j] == symbols), (i-1, j)),
        ((l[i-1][j-1] == symbols), (i-1, j-1)),
        ((l[i+1][j+1] == symbols), (i+1, j+1)),
        ((l[i-1][j+1] == symbols), (i-1, j+1)),
        ((l[i+1][j-1] == symbols), (i+1, j-1)),
    ]

    for condition, pos in conditions:
        if condition:
            return True, pos
    return False, (0, 0)  # Default position if not found

s = ""
res = 0
num = []
gear = (0, 0)
b= False 

for i in range(len(l)):
    for j in range(len(l[0])):
        if len(num) == 2:
            res += num[0] * num[1]
            num = []
        if '0' <= l[i][j] <= '9':
            tmp, pos = is_symbol_near(l, i, j)
            if tmp and pos != gear :
                num = []
                gear = pos
            b = b or tmp
            s += str(l[i][j])

        if s and (l[i][j] < '0' or l[i][j] > '9'):
            if b :
                num.append(int(s))
            b = False
            s = ""
print(res)
print(res == 78915902)

