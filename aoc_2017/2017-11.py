import math

path = ''
with open('/home/leaves/Code/AdventOfCode/aoc_2017/day11.txt', 'r') as file:
    path = file.readline().split(',')
x = 0
y = 0

max_dist = 0
for d in path:
    if d == 'n':
        y += 1
    elif d == 's':
        y -= 1
    elif d == 'nw':
        if x % 2 == 1:
            y += 1
        x -= 1
    elif d == 'ne':
        if x % 2 == 1:
            y += 1
        x += 1
    elif d == 'sw':
        if x % 2 == 0:
            y -= 1
        x -= 1
    elif d == 'se':
        if x % 2 == 0:
            y -= 1
        x += 1

    dist = abs(x)
    dist += abs(y) - min(math.ceil(abs(x) / 2), abs(y))
    max_dist = max(max_dist, dist)


dist = abs(x)
dist += abs(y) - min(math.ceil(abs(x) / 2), abs(y))
print(f'part 1: {dist}')
print(f'part 2: {max_dist}')

# time: 21:15