from copy import deepcopy

LASER_CHARS = ["|", "S"]


def solve_part_1(manifold: list[list[str]]) -> int:
    splits = 0
    for i in range(1, len(manifold)):
        for j in range(len(manifold[0])):
            if manifold[i - 1][j] in LASER_CHARS:
                if manifold[i][j] == "^":
                    if j - 1 >= 0:
                        manifold[i][j - 1] = "|"
                    if j + 1 < len(manifold[0]):
                        manifold[i][j + 1] = "|"
                    splits += 1
                else:
                    manifold[i][j] = "|"

    # image = "\n".join(["".join(arr) for arr in manifold])
    # print(image)

    return splits


def solve_part_2(manifold: list[list[str]]) -> int:
    # number of timelines a particle can be at at that square
    timelines = [[0 for _ in range(len(manifold[0]))] for _ in range(len(manifold))]
    for i in range(len(manifold[0])):
        if manifold[0][i] in LASER_CHARS:
            timelines[0][i] = 1

    for i in range(1, len(manifold)):
        for j in range(len(manifold[0])):
            if manifold[i - 1][j] in LASER_CHARS:
                if manifold[i][j] == "^":
                    if j - 1 >= 0:
                        manifold[i][j - 1] = "|"
                        timelines[i][j - 1] += timelines[i - 1][j]
                    if j + 1 < len(manifold[0]):
                        manifold[i][j + 1] = "|"
                        timelines[i][j + 1] += timelines[i - 1][j]
                else:
                    manifold[i][j] = "|"
                    timelines[i][j] += timelines[i - 1][j]

    return sum(timelines[-1])


manifold: list[list[str]] = []
line = input()
while line != "":
    manifold.append([c for c in line])
    line = input()

print(f"part 1: {solve_part_1(deepcopy(manifold))}")
print(f"part 2: {solve_part_2(deepcopy(manifold))}")
