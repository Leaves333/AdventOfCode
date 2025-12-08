def solve_part_1(ranges: list[list[int]], ids: list[int]) -> int:
    ans = 0
    for x in ids:
        for a, b in ranges:
            if x >= a and x <= b:
                ans += 1
                break
    return ans


def solve_part_2(ranges: list[list[int]]) -> int:
    intervals = sorted(ranges)
    for i in range(len(intervals) - 1, 0, -1):
        if intervals[i][0] <= intervals[i - 1][1]:
            intervals[i - 1][1] = max(intervals[i][1], intervals[i - 1][1])
            intervals.pop(i)

    ans = 0
    for a, b in intervals:
        ans += b - a + 1
    return ans


ranges: list[list[int]] = []
line = input()
while line != "":
    (a, b) = map(int, line.split("-"))
    ranges.append([a, b])
    line = input()

ids: list[int] = []
line = input()
while line != "":
    ids.append(int(line))
    line = input()

print(f"part 1: {solve_part_1(ranges, ids)}")
print(f"part 2: {solve_part_2(ranges)}")
