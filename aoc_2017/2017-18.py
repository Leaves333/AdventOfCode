instructions = []

line = input()
while line != '':
    inp = line.split()
    instructions.append(inp)
    line = input()

register = dict()
pos = 0
last_played = -1

while pos < len(instructions):

    inst = instructions[pos]
    first = inst[1]
    if first not in register.keys():
        register[first] = 0
    
    second = None
    if len(inst) >= 3:
        if str(inst[2]).isalpha():
            second = register[inst[2]]
        else:
            second = int(inst[2])

    if inst[0] == 'snd':
        last_played = register[inst[1]]
    elif inst[0] == 'set':
        register[first] = second
    elif inst[0] == 'add':
        register[first] += second
    elif inst[0] == 'mul':
        register[first] *= second
    elif inst[0] == 'mod':
        register[first] %= second
    elif inst[0] == 'rcv':
        if register[first] != 0:
            print(last_played)
            break
    elif inst[0] == 'jgz':
        if register[first] > 0:
            pos += second - 1

    pos += 1

### part 2

register = [dict(), dict()]
register[0]['p'] = 0
register[1]['p'] = 1
queue = [[], []]
pos = [0, 0]
current_program = 0
values_sent = 0

def other_program():
    global current_program
    if current_program == 0:
        return 1
    else:
        return 0

while True:

    inst = instructions[pos[current_program]]
    first = inst[1]
    if first.isalpha() and first not in register[current_program].keys():
        register[current_program][first] = 0
    elif first not in register[current_program].keys():
        register[current_program][first] = int(first) #jank af
    
    second = None
    if len(inst) >= 3:
        if str(inst[2]).isalpha():
            second = register[current_program][inst[2]]
        else:
            second = int(inst[2])

    if inst[0] == 'snd':
        queue[other_program()].append(register[current_program][first])
        if current_program == 1:
            values_sent += 1
    elif inst[0] == 'set':
        register[current_program][first] = second
    elif inst[0] == 'add':
        register[current_program][first] += second
    elif inst[0] == 'mul':
        register[current_program][first] *= second
    elif inst[0] == 'mod':
        register[current_program][first] %= second
    elif inst[0] == 'rcv':
        if len(queue[current_program]) > 0:
            register[current_program][first] = queue[current_program].pop(0)
        else:
            current_program = other_program()
            if len(queue[current_program]) == 0:
                break
            continue
    elif inst[0] == 'jgz':
        if register[current_program][first] > 0:
            pos[current_program] += second - 1

    pos[current_program] += 1

print(values_sent)

# time: 1:05:14
# completely screwed up this one by not reading carefully whoops