INPUT_SIZE = 43

rules = {}
starting_string = ""

with open("input.txt") as file:
    for i in range(INPUT_SIZE):
        line = file.readline().split(" ")
        if not line[0] in rules:
            rules[line[0]] = []
        rules[line[0]].append(line[2].rstrip("\n"))
    
    file.readline()
    starting_string = file.readline()

possible_strings = []
for s in rules.keys():
    last_pos = 0
    while starting_string.find(s, last_pos) != -1:
        last_pos = starting_string.find(s, last_pos) + len(s)
        for ss in rules[s]:
            new_string = starting_string[:last_pos - len(s)] + ss + starting_string[last_pos:]
            if not new_string in possible_strings:
                possible_strings.append(new_string)
                #print(new_string)

shortest = 100000000
k = 0
checked = {}
def recur(string, i):

    global shortest
    global k;
    k += 1;
    if k % 10000 == 0:
        print(string)
        print(k)
    #print(string + " : " + str(i))

    if string == "e" and i < shortest:
        shortest = i
        return

    if not string in checked:
        checked[string] = 0
        for key, value in rules.items():
            for v in value:
                if string.find(v) != -1:
                    pos = string.find(v)
                    recur(string[:pos] + key + string[pos + len(v):], i + 1)
                    return

recur(starting_string, 0)
print(len(possible_strings))
print(shortest)