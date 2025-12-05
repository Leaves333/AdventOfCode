part_1 = 0
part_2 = 0


def max_index(line: str, left: int, right: int) -> int:
    idx = left
    for j in range(left, right):
        if line[j] > line[idx]:
            idx = j
    return idx


def solve_part_two(line: str) -> int:
    pref = ""
    suff = ""
    left = 0
    right = len(line)

    while len(pref) + len(suff) < 12:
        i = max_index(line, left, right)

        # enough digits on the right to make 12?
        remaining_digits = right - i
        if remaining_digits + len(pref) + len(suff) >= 12:
            pref += line[i]
            left = i + 1

        # not enough, all remaining should be a suffix
        else:
            suff = line[i:right] + suff
            right = i

    return int(pref + suff)


line = input()
while line != "":
    max_digit = "0"
    max_idx = -1
    for i in range(len(line)):
        if line[i] > max_digit:
            max_digit = line[i]
            max_idx = i

    second_max = "0"
    if max_idx == len(line) - 1:
        for i in range(len(line) - 1):
            if line[i] > second_max:
                second_max = line[i]
        tmp = max_digit
        max_digit = second_max
        second_max = tmp
    else:
        for i in range(max_idx + 1, len(line)):
            if line[i] > second_max:
                second_max = line[i]

    val = int(max_digit) * 10 + int(second_max)
    part_1 += val
    part_2 += solve_part_two(line)
    line = input()

print(f"part 1: {part_1}")
print(f"part 2: {part_2}")
