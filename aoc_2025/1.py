from math import floor

part_1 = 0
part_2 = 0
line = input()
cur = 50
while line != "":
    dir = line[0]
    val = int(line[1:])

    prev = cur
    if dir == "R":
        cur += val
    else:
        cur -= val

    while prev < cur:
        prev += 1
        if prev % 100 == 0:
            part_2 += 1
    while prev > cur:
        prev -= 1
        if prev % 100 == 0:
            part_2 += 1

    cur %= 100
    if cur == 0:
        part_1 += 1
    line = input()

print(f"part 1: {part_1}")
print(f"part 2: {part_2}")
# 6591 too low
