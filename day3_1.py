
l = []

with open('input/day3.txt', 'r') as f:
    for line in f:
        l.append(line)

symbols = []
for i in l:
    for it in i:
        if it != '.' and (it < '0' or it > '9') and it not in symbols and it != '\n':
            symbols.append(it)

def is_symbol_near_i(l, i, j):
    b = False

    if i == 0 and j != 0 and j != len(l)-1:
        conditions = [
            (l[i+1][j] in symbols),
            (l[i+1][j+1] in symbols),
            (l[i+1][j-1] in symbols),
        ]
        b = any(conditions)

    elif i == len(l) - 1:
        conditions = [
            (l[i-1][j] in symbols),
            (l[i-1][j+1] in symbols),
            (l[i-1][j-1] in symbols),
        ]
        b = any(conditions)

    return b

def is_symbol_near(l, i, j):
    if i == 0 or i == len(l) - 1 or j == 0 or j == len(l[0]) - 1:
        return is_symbol_near_i(l, i, j)

    return (
        (j+1 < len(l[0]) and l[i][j+1] in symbols) or
        (j-1 >= 0 and l[i][j-1] in symbols) or
        (i+1 < len(l) and l[i+1][j] in symbols) or
        (i-1 >= 0 and l[i-1][j] in symbols) or
        (i-1 >= 0 and j-1 >= 0 and l[i-1][j-1] in symbols) or
        (i+1 < len(l) and j+1 < len(l[0]) and l[i+1][j+1] in symbols) or
        (i-1 >= 0 and j+1 < len(l[0]) and l[i-1][j+1] in symbols) or
        (i+1 < len(l) and j-1 >= 0 and l[i+1][j-1] in symbols)
    )

s = ""
b = False
res = 0
for i in range(len(l)):
    for j in range(len(l[0])):
        s += str(l[i][j]) if '0' <= l[i][j] <= '9' else ''
        if s and (l[i][j] < '0' or l[i][j] > '9'):
            print(s)
            res += int(s) if b else 0
            b = False
            s = ""
        if '0' <= l[i][j] <= '9':
            b = b or is_symbol_near(l, i, j)

print(res)
