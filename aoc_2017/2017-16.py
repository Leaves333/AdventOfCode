# sample: s1,x3/4,pe/b

letters = 'abcdefghijklmnop'
arr = [x for x in letters]

commands = ''
with open('/home/leaves/Code/AdventOfCode/aoc_2017/day16.txt', 'r') as file:
    commands = file.readline().split(',')

for c in commands:
    if c[0] == 's':
        x = int(c[1:])
        arr = arr[x * -1:] + arr[:x * -1]
    elif c[0] == 'x':
        a, b = map(int, c[1:].split('/'))
        tmp = arr[a]
        arr[a] = arr[b]
        arr[b] = tmp
    elif c[0] == 'p':
        a, b = c[1:].split('/')
        x = arr.index(a)
        y = arr.index(b)
        tmp = arr[x]
        arr[x] = arr[y]
        arr[y] = tmp

one = ''
for c in arr:
    one += c
print(one)

def stringify(arr):
    two = ''
    for c in arr:
        two += c
    return two

arr = [x for x in letters]
previous = []
previous.append(stringify(arr))

stop = -1
for i in range(999999999):
    for c in commands:
        if c[0] == 's':
            x = int(c[1:])
            arr = arr[x * -1:] + arr[:x * -1]
        elif c[0] == 'x':
            a, b = map(int, c[1:].split('/'))
            tmp = arr[a]
            arr[a] = arr[b]
            arr[b] = tmp
        elif c[0] == 'p':
            a, b = c[1:].split('/')
            x = arr.index(a)
            y = arr.index(b)
            tmp = arr[x]
            arr[x] = arr[y]
            arr[y] = tmp

    s = stringify(arr)
    if s in previous:
        stop = i
        break
    else:
        previous.append(s)

period = stop - previous.index(stringify(arr)) + 1
mod = 1000000000 % period
idx = previous.index(stringify(arr))
print(previous[(idx + mod) % period])

# time: 19:35