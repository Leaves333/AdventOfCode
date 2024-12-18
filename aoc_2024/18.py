from queue import PriorityQueue
import sys
sys.setrecursionlimit(71 * 71)

GRID_SIZE = 71
BYTES_FALLEN = 1024

# util func
def in_bounds(x: int, y: int) -> bool:
    return x >= 0 and y >= 0 and x < GRID_SIZE and y < GRID_SIZE

def can_reach_end(x: int, y: int, seen: set[tuple[int, int]], grid: list[list[bool]]) -> bool:
    seen.add((x, y))
    if x == GRID_SIZE - 1 and y == GRID_SIZE - 1: return True
    good = False
    changes = [[0, -1], [0, 1], [1, 0], [-1, 0]]
    for c in changes:
        new_x = x + c[0]
        new_y = y + c[1]
        if not in_bounds(new_x, new_y): continue
        if not grid[new_x][new_y]: continue
        if (new_x, new_y) in seen: continue
        good |= can_reach_end(new_x, new_y, seen, grid)
    return good

# read input
# true is empty, false is wall
grid = [[True for _ in range(GRID_SIZE)] for _ in range(GRID_SIZE)]
with open("input.txt", "r") as file:
    lines = file.read().split("\n")

for i in range(BYTES_FALLEN):
    a, b = map(int, lines[i].split(","))
    grid[a][b] = False

INT_MAX = 1000000
dist = [[INT_MAX for _ in range(GRID_SIZE)] for _ in range(GRID_SIZE)]
dist[0][0] = 0

# dist, (x, y)
pq: PriorityQueue[tuple[int, tuple[int, int]]] = PriorityQueue()
pq.put((0, (0, 0)))

while pq.qsize() > 0:
    cur_dist, (x, y) = pq.get()
    changes = [[0, -1], [0, 1], [1, 0], [-1, 0]]
    for c in changes:
        new_x = x + c[0]
        new_y = y + c[1]
        if not in_bounds(new_x, new_y): continue
        if not grid[new_x][new_y]: continue
        if cur_dist + 1 >= dist[new_x][new_y]: continue
        dist[new_x][new_y] = cur_dist + 1
        pq.put((cur_dist + 1, (new_x, new_y)))

print(f"part 1: {dist[-1][-1]}")

for i in range(BYTES_FALLEN, len(lines)):
    a, b = map(int, lines[i].split(","))
    grid[a][b] = False
    if not can_reach_end(0, 0, set(), grid):
        print(f"part 2: {a},{b}")
        break
