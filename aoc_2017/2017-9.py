line = ''
with open('/home/leaves/Code/AdventOfCode/aoc_2017/day9.txt', 'r') as file:
    line = file.readline()
garbage = False
skip = False
score = 0
depth = 0
canceled = 0

for i in range(len(line)):

    if skip:
        skip = False
        continue

    if line[i] == '<' and not garbage:
        garbage = True
        continue
    if line[i] == '>' and garbage:
        garbage = False
        continue
    if line[i] == '!' and garbage:
        skip = True
        continue

    if garbage:
        canceled += 1
        continue

    if line[i] == '{':
        depth += 1
        continue
    if line[i] == '}':
        score += depth
        depth -= 1
        continue

print(f'part 1: {score}')
print(f'part 2: {canceled}')

# time 47:54
# the problem itself wasn't hard, but i had issues getting it to read the whole input for some reason