from copy import deepcopy
import math


class DSU:
    def __init__(self, n) -> None:
        self.parent = [i for i in range(n)]
        self.size = [1 for _ in range(n)]

    def find_set(self, v) -> int:
        if v == self.parent[v]:
            return v
        self.parent[v] = self.find_set(self.parent[v])
        return self.parent[v]

    def union_sets(self, a, b):
        a = self.find_set(a)
        b = self.find_set(b)
        if a == b:
            return
        if self.size[a] < self.size[b]:
            a, b = b, a
        self.parent[b] = a
        self.size[a] += self.size[b]


class Point:
    def __init__(self, x: int, y: int, z: int) -> None:
        self.x = x
        self.y = y
        self.z = z


def distance(a: Point, b: Point) -> int:
    """returns square distance between two points"""
    return (a.x - b.x) ** 2 + (a.y - b.y) ** 2 + (a.z - b.z) ** 2


def solve(circuits: list[Point]) -> tuple[int, int]:
    edges: list[tuple[int, int, int]] = []  # dist, idx a, idx b
    for i in range(len(circuits)):
        for j in range(i + 1, len(circuits)):
            edges.append((distance(circuits[i], circuits[j]), i, j))
    edges = sorted(edges)

    dsu = DSU(len(circuits))
    for i in range(1000):
        (dist, a, b) = edges[i]
        dsu.union_sets(a, b)
    leaders = set([dsu.find_set(x) for x in range(len(circuits))])
    sizes = list(reversed(sorted(dsu.size[x] for x in leaders)))
    one = math.prod(sizes[:3])

    two = -1
    dsu = DSU(len(circuits))
    for i in range(len(edges)):
        (dist, a, b) = edges[i]
        dsu.union_sets(a, b)
        if dsu.size[dsu.find_set(a)] == len(circuits):
            two = circuits[a].x * circuits[b].x
            break

    return (one, two)


circuits: list[Point] = []
line = input()
while line != "":
    (a, b, c) = map(int, line.split(","))
    circuits.append(Point(a, b, c))
    line = input()

(one, two) = solve(circuits)
print(f"part 1: {one}")
print(f"part 2: {two}")
