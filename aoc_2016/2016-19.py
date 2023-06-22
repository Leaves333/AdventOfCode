from math import ceil

starting_elves = 3001330

elves = []
for i in range(1, starting_elves + 1):
    elves.append(i)

#do part 1
if False:
    while len(elves) != 1:
        new_list = []
        if len(elves) % 2 == 0:
            for i in range(0, len(elves), 2):
                new_list.append(elves[i])
        else:
            for i in range(2, len(elves), 2):
                new_list.append(elves[i])
        elves = new_list

    if len(elves) == 1:
        print(elves[0])

while len(elves) != 1:
    opposite_side = []
    if len(elves) % 2 == 0:
        for i in range(int(len(elves) / 2) + 2, len(elves), 3):
            opposite_side.append(elves[i])
    else:
        for i in range(int(len(elves) / 2) + 1, len(elves), 3):
            opposite_side.append(elves[i])
    remaining = elves[ceil(len(elves) / 2) - len(opposite_side):int(len(elves) / 2)]
    remaining.extend(opposite_side)
    remaining.extend(elves[:ceil((len(elves) / 2) - len(opposite_side))])
    elves = remaining

print(elves[0])
    
    