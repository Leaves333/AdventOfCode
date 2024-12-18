with open("input.txt", "r") as file:
    a = int(file.readline().split(": ")[1])
    b = int(file.readline().split(": ")[1])
    c = int(file.readline().split(": ")[1])
    file.readline() # empty line
    program = list(map(int, file.readline().split(": ")[1].split(",")))

def combo_value(x: int) -> int:
    if x <= 3:
        return x
    if x == 4:
        return a
    if x == 5:
        return b
    if x == 6:
        return c
    return 0

idx = 0
output = ""
while idx < len(program):
    opcode = program[idx]
    if opcode == 0:
        a = a >> combo_value(program[idx + 1])
    if opcode == 1:
        b = b ^ program[idx + 1]
    if opcode == 2:
        b = combo_value(program[idx + 1]) % 8
    if opcode == 3:
        if a != 0:
            idx = program[idx + 1]
            continue
    if opcode == 4:
        b = b ^ c
    if opcode == 5:
        output += str(combo_value(program[idx + 1]) % 8) + ","
    if opcode == 6:
        b = a >> combo_value(program[idx + 1])
    if opcode == 7:
        c = a >> combo_value(program[idx + 1])
    idx += 2

print("part 1: " + output[:len(output) - 1])
