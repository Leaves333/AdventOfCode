import math


def solve_part_1(vals: list[list[int]], ops: list[str]) -> int:
    ans = 0
    for i in range(len(ops)):
        cur = 1 if ops[i] == "*" else 0
        for j in range(len(vals)):
            if ops[i] == "*":
                cur *= vals[j][i]
            else:
                cur += vals[j][i]
        ans += cur
    return ans


def solve_part_2(lines: list[str]) -> int:
    ops = lines[-1].split()
    slices: list[list[str]] = []

    # check if column is all spaces
    last_cut = 0
    for i in range(len(lines[0])):
        all_spaces = True
        for line in lines[:-1]:
            if line[i] != " ":
                all_spaces = False
                break
        if all_spaces:
            cur_slice = []
            for line in lines[:-1]:
                cur_slice.append(line[last_cut:i])
            last_cut = i + 1
            slices.append(cur_slice)

    # edge case to get the last slice
    cur_slice = []
    for line in lines[:-1]:
        cur_slice.append(line[last_cut:])
    slices.append(cur_slice)

    ans = 0
    for i in range(len(slices)):
        matrix = [[c for c in word] for word in slices[i]]
        transpose = list(zip(*matrix))
        vals = [int("".join(tup).lstrip().rstrip()) for tup in transpose]
        if ops[i] == "*":
            ans += math.prod(vals)
        else:
            ans += sum(vals)
    return ans


inp = input()
lines: list[str] = []
vals: list[list[int]] = []
ops: list[str] = []

while inp != "":
    lines.append(inp)
    inp = input()

for line in lines[:-1]:
    vals.append(list(map(int, line.split())))
ops = lines[-1].split()

print(f"part 1: {solve_part_1(vals, ops)}")
print(f"part 2: {solve_part_2(lines)}")
