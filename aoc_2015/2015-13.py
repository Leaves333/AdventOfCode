import itertools

paths = {}

with open("input.txt") as file:
    for i in range(72):
        inputs = file.readline().split(" ")
        inputs[10] = inputs[10].rstrip('.\n')
        #print(inputs[10])
        if not inputs[0] in paths:
            paths[inputs[0]] = {}
        value = int(inputs[3])
        if inputs[2] == "lose":
            value *= -1
        paths[inputs[0]][inputs[10]] = value

keys = []
for x in paths.keys():
    keys.append(x)

perms = list(itertools.permutations(keys))

max_happiness = 0
for t in perms:
    cur_happiness = 0
    for i in range(len(t)):
        if i != len(t) - 1:
            cur_happiness += paths[t[i]][t[i + 1]]
        else:
            cur_happiness += paths[t[i]][t[0]]
        if i != 0:
            cur_happiness += paths[t[i]][t[i - 1]]
        else:
            cur_happiness += paths[t[i]][t[len(t) - 1]]
    if cur_happiness > max_happiness:
        max_happiness = cur_happiness

print(max_happiness)
