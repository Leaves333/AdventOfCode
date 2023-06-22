reg = dict()
line = input()

two = -696969
while line != '':

    instructions = line.split()

    loc = instructions[0]
    if loc not in reg.keys():
        reg[loc] = 0
    
    read = instructions[4]
    if read not in reg.keys():
        reg[read] = 0

    good = eval(f'{reg[read]} {instructions[5]} {instructions[6]}')
    if good:
        if instructions[1] == 'inc':
            reg[loc] += int(instructions[2])
        elif instructions[1] == 'dec':
            reg[loc] -= int(instructions[2])

    for value in reg.values():
        if value > two:
            two = value

    line = input()

one = -696969
for value in reg.values():
    if value > one:
        one = value

print(f'part 1: {one}')
print(f'part 2: {two}')

# time: 7:52