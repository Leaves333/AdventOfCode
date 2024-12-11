from collections import defaultdict


with open("input.txt", "r") as file:
    stones = list(file.readline().split())

ct: defaultdict[str, int] = defaultdict(int)
for stone in stones:
    ct[stone] += 1

for _ in range(25):
    new_ct = defaultdict(int)
    for key, count in ct.items():
        val = int(key)
        if val == 0:
            new_ct["1"] += count
        elif len(key) % 2 == 0:
            new_ct[key[:len(key) // 2]] += count
            new_ct[str(int(key[len(key) // 2:]))] += count
        else:
            new_ct[str(val * 2024)] += count
    ct = new_ct

print(f"part 1: {sum(ct.values())}")

for _ in range(50):
    new_ct = defaultdict(int)
    for key, count in ct.items():
        val = int(key)
        if val == 0:
            new_ct["1"] += count
        elif len(key) % 2 == 0:
            new_ct[key[:len(key) // 2]] += count
            new_ct[str(int(key[len(key) // 2:]))] += count
        else:
            new_ct[str(val * 2024)] += count
    ct = new_ct

print(f"part 2: {sum(ct.values())}")
