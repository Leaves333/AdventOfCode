import itertools
import time
import copy
from typing import Any


class Present:
    def __init__(self) -> None:
        self.shape: list[list[str]] = [
            [".", ".", "."],
            [".", ".", "."],
            [".", ".", "."],
        ]

    def __str__(self) -> str:
        return "\n".join(
            ["".join(c for c in self.shape[i]) for i in range(len(self.shape))]
        )

    def rotate(self) -> "Present":
        """returns this present rotated 90 degrees CCW"""
        rotated = Present()
        for i, j in itertools.product([0, 1, 2], repeat=2):
            rotated.shape[i][j] = self.shape[j][2 - i]
        return rotated

    def squares(self) -> int:
        area = 0
        for row in self.shape:
            for c in row:
                if c == "#":
                    area += 1
        return area


class Region:
    def __init__(self, width: int, height: int, counts: list[int]) -> None:
        self.width = width
        self.height = height
        self.counts = counts


line: str = ""
shapes: list[Present] = []

while True:
    line = input()
    if line[-1] == ":":
        present = Present()
        for i in range(3):
            line = input()
            present.shape[i] = [c for c in line]
        line = input()
        shapes.append(present)
    else:
        break

regions: list[Region] = []
while line != "":
    (size_str, counts_str) = line.split(": ")
    (h, w) = map(int, size_str.split("x"))
    counts = list(map(int, counts_str.split()))
    regions.append(Region(h, w, counts))
    line = input()


def grid_to_string(grid: list[list[str]]) -> str:
    return "\n".join(["".join(c for c in grid[i]) for i in range(len(grid))])


def can_fit(grid: list[list[str]], x: int, y: int, present: Present) -> bool:
    """given a grid, present, position, does it fit?"""

    # print("can_fit called:")
    # print("grid:")
    # print(grid_to_string(grid))
    # print("present:")
    # print(present)
    # print((x, y))

    for i, j in itertools.product([0, 1, 2], repeat=2):
        if present.shape[i][j] != "#":
            continue
        if grid[x + i][y + j] == "#":
            # print("return false.")
            # print()
            return False
    # print("return true.")
    # print()
    return True


def place_present(grid: list[list[str]], x: int, y: int, present: Present):
    """places the given present at this location in the grid"""
    for i, j in itertools.product([0, 1, 2], repeat=2):
        if present.shape[i][j] != "#":
            continue
        grid[x + i][y + j] = "#"


def remove_present(grid: list[list[str]], x: int, y: int, present: Present):
    """removes the given present at this location in the grid"""
    for i, j in itertools.product([0, 1, 2], repeat=2):
        if present.shape[i][j] != "#":
            continue
        grid[x + i][y + j] = "."


solve_memo: dict[Any, bool] = {}


def can_solve(
    grid: list[list[str]], remaining: list[int], shapes: list[Present]
) -> bool:
    """
    given a grid with the remaining shapes we need to put,
    returns True if we can put all of them on the grid and false otherwise
    """

    if (grid_to_string(grid), tuple(remaining)) in solve_memo:
        return solve_memo[(grid_to_string(grid), tuple(remaining))]

    print(f"solving: {remaining}")
    print("grid:")
    print(grid_to_string(grid))

    # if no more shapes to place, we're good
    all_done = True
    for x in remaining:
        if x != 0:
            all_done = False
            break
    if all_done:
        return True

    for shape_idx in range(len(remaining)):  # try all shapes
        # do we have more shapes of this type to place?
        if remaining[shape_idx] <= 0:
            continue
        present = copy.copy(shapes[shape_idx])

        for _ in range(4):  # try each rotation
            for x in range(len(grid) - 2):  # try each position
                for y in range(len(grid[0]) - 2):
                    if not can_fit(grid, x, y, present):  # does it fit?
                        continue

                    # recurse!
                    place_present(grid, x, y, present)
                    remaining[shape_idx] -= 1
                    result = can_solve(grid, remaining, shapes)
                    if result:
                        solve_memo[(grid_to_string(grid), tuple(remaining))] = True
                        return True
                    remaining[shape_idx] += 1
                    remove_present(grid, x, y, present)

            present = present.rotate()

    solve_memo[(grid_to_string(grid), tuple(remaining))] = False
    return False


def solve_part_1(shapes: list[Present], regions: list[Region]) -> int:
    ans = 0
    for region in regions:
        total_area = region.width * region.height
        area_needed = 0
        for i in range(len(shapes)):
            area_needed += shapes[i].squares() * region.counts[i]
        if area_needed < total_area:
            ans += 1

        continue
        grid = [["." for _ in range(region.width)] for _ in range(region.height)]
        remaining = copy.copy(region.counts)
        if can_solve(grid, remaining, shapes):
            ans += 1
    return ans


start = time.time()
print(f"part 1: {solve_part_1(shapes, regions)}")
end = time.time()
print(f"time: {end - start:.3f}s")
