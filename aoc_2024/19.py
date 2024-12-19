with open("input.txt", "r") as file:
    patterns = set(file.readline()[:-1].split(", "))
    file.readline() # empty line

    lines = file.read().split("\n")[:-1]

def can_form_pattern(target: str, idx: int, seen_indexes: set[int]) -> bool:
    seen_indexes.add(idx)
    found = False
    cur_substr = ""
    for i in range(idx, len(target)):
        cur_substr += target[i]
        if cur_substr in patterns and i + 1 not in seen_indexes:
            found |= can_form_pattern(target, i + 1, seen_indexes)
    if idx == len(target):
        found = True
    return found

print(patterns)
part_1 = 0
part_2 = 0
for line in lines:
    print(f"checking {line}...")
    seen_indexes = set()
    if can_form_pattern(line, 0, seen_indexes):
        part_1 += 1
        print("good!")

    dp = [0 for _ in range(len(line) + 1)]
    dp[len(line)] = 1
    for i in range(len(line) - 1, -1, -1):
        cur_substr = ""
        for j in range(i, len(line)):
            cur_substr += line[j]
            if cur_substr in patterns:
                dp[i] += dp[j + 1]

    part_2 += dp[0]
    print(dp)
    print()

print(f"part 1: {part_1}")
print(f"part 2: {part_2}")
