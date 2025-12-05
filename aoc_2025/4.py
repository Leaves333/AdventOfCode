from copyreg import remove_extension
import itertools


def count_adjacent(grid: list[list[str]], x: int, y: int) -> int:
    num_adj = 0
    for dx, dy in itertools.product([-1, 0, 1], repeat=2):
        new_x = x + dx
        new_y = y + dy
        if new_x < 0 or new_x >= len(grid) or new_y < 0 or new_y >= len(grid[0]):
            continue
        if grid[new_x][new_y] == "@":
            num_adj += 1
    return num_adj


def solve_part_1(grid: list[list[str]]) -> int:
    ans = 0
    for x in range(len(grid)):
        for y in range(len(grid[0])):
            if grid[x][y] != "@":
                continue
            if count_adjacent(grid, x, y) <= 4:
                ans += 1
    return ans


def solve_part_2(grid: list[list[str]]) -> int:
    ans = 0
    to_check: list[tuple[int, int]] = []
    for x in range(len(grid)):
        for y in range(len(grid[0])):
            to_check.append((x, y))

    while len(to_check) > 0:
        (x, y) = to_check.pop()
        if grid[x][y] != "@":
            continue

        if count_adjacent(grid, x, y) <= 4:
            ans += 1
            grid[x][y] = "."

            for dx, dy in itertools.product([-1, 0, 1], repeat=2):
                new_x = x + dx
                new_y = y + dy
                if (
                    new_x < 0
                    or new_x >= len(grid)
                    or new_y < 0
                    or new_y >= len(grid[0])
                ):
                    continue
                to_check.append((new_x, new_y))

    return ans


grid: list[list[str]] = []
line = input()
while line != "":
    grid.append([c for c in line])
    line = input()

print(f"part_1: {solve_part_1(grid)}")
print(f"part_2: {solve_part_2(grid)}")
