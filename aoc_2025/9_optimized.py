import time


class Point:
    def __init__(self, x: int, y: int) -> None:
        self.x = x
        self.y = y

    def __str__(self) -> str:
        return f"({self.x}, {self.y})"


def solve_part_1(tiles: list[Point]) -> int:
    area = 0
    for i in range(len(tiles)):
        for j in range(i + 1, len(tiles)):
            a, b = tiles[i], tiles[j]
            new_area = (abs(a.x - b.x) + 1) * (abs(a.y - b.y) + 1)
            area = max(area, new_area)
    return area


def solve_part_2(tiles: list[Point]) -> int:
    # compress coordinates
    x_set: set[int] = set()
    y_set: set[int] = set()
    for point in tiles:
        x_set.add(point.x)
        y_set.add(point.y)

    x_list: list[int] = sorted(x for x in x_set)
    y_list: list[int] = sorted(y for y in y_set)

    x_dict: dict[int, int] = {x_list[i]: i * 2 for i in range(len(x_set))}
    y_dict: dict[int, int] = {y_list[i]: i * 2 for i in range(len(y_set))}

    # perform the brute force algorithm
    # '.' is empty, '#' is block, 'x' is flood filled
    grid: list[list[str]] = [
        ["." for _ in range(len(y_set) * 2)] for _ in range(len(x_set) * 2)
    ]

    # fill in line segments around the outside
    for i in range(len(tiles)):
        j = (i + 1) % len(tiles)
        x1, y1 = x_dict[tiles[i].x], y_dict[tiles[i].y]
        x2, y2 = x_dict[tiles[j].x], y_dict[tiles[j].y]

        dx = 0
        if x1 > x2:
            dx = -1
        elif x1 < x2:
            dx = 1

        dy = 0
        if y1 > y2:
            dy = -1
        elif y1 < y2:
            dy = 1

        while (x1, y1) != (x2, y2):
            grid[x1][y1] = "#"
            x1 += dx
            y1 += dy
        grid[x1][y1] = "#"

    # find a coord to start the fill
    # scan along x=1, wait for first empty square after '#'
    queue: list[Point] = []
    for i in range(len(grid[0])):
        if grid[1][i] == "#":
            grid[1][i + 1] = "#"
            queue.append(Point(1, i + 1))
            break

    # flood fill
    while len(queue) > 0:
        cur = queue.pop()

        DIRS = [Point(0, 1), Point(0, -1), Point(1, 0), Point(-1, 0)]
        for d in DIRS:
            new_x, new_y = cur.x + d.x, cur.y + d.y
            if new_x < 0 or new_y < 0:
                continue
            if grid[new_x][new_y] == "#":
                continue
            grid[new_x][new_y] = "#"
            queue.append(Point(new_x, new_y))

    # loop over all rectangles
    area = 0
    for i in range(len(tiles)):
        for j in range(i + 1, len(tiles)):
            first, second = tiles[i], tiles[j]
            new_area = (abs(first.x - second.x) + 1) * (abs(first.y - second.y) + 1)

            x1, y1 = x_dict[first.x], y_dict[first.y]
            x2, y2 = x_dict[second.x], y_dict[second.y]

            # check horizontal edges
            good = True
            for x in range(min(x1, x2), max(x1, x2) + 1):
                if grid[x][y1] != "#":
                    good = False
                if grid[x][y2] != "#":
                    good = False
                if not good:
                    break

            # check vertical edges
            for y in range(min(y1, y2), max(y1, y2) + 1):
                if grid[x1][y] != "#":
                    good = False
                if grid[x2][y] != "#":
                    good = False
                if not good:
                    break

            if good:
                area = max(area, new_area)
    return area


tiles: list[Point] = []
line = input()
while line != "":
    a, b = map(int, line.split(","))
    tiles.append(Point(a, b))
    line = input()


start = time.time()
print(f"part 1: {solve_part_1(tiles)}")
print(f"part 2: {solve_part_2(tiles)}")
end = time.time()
print(f"time: {end - start:.3f}s")
