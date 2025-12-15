import time

graph: dict[str, list[str]] = {}

line = input()
while line != "":
    (src, dest_str) = line.split(": ")
    graph[src] = dest_str.split()
    line = input()


class PathData:
    def __init__(self) -> None:
        self.neither = 0
        self.dac = 0
        self.fft = 0
        self.both = 0

    def __str__(self) -> str:
        return f"PathData(neither: {self.neither}, dac: {self.dac}, fft: {self.fft}, both: {self.both})"


def rev(graph: dict[str, list[str]]) -> dict[str, list[str]]:
    rev_graph: dict[str, list[str]] = {}
    for key in graph:
        dests = graph[key]
        if key not in rev_graph:
            rev_graph[key] = []
        for d in dests:
            if d not in rev_graph:
                rev_graph[d] = []
            rev_graph[d].append(key)
    return rev_graph


def dfs_simple(v: str, rev_graph: dict[str, list[str]], paths: dict[str, int]) -> int:
    if v == "you":
        return 1
    if v not in paths:
        paths[v] = 0
        for prev in rev_graph[v]:
            paths[v] += dfs_simple(prev, rev_graph, paths)
    return paths[v]


def dfs_complex(
    v: str, rev_graph: dict[str, list[str]], paths: dict[str, PathData]
) -> PathData:
    if v == "svr":
        data = PathData()
        data.neither = 1
        return data
    if v not in paths:
        paths[v] = PathData()
        for prev in rev_graph[v]:
            other = dfs_complex(prev, rev_graph, paths)
            if v == "fft":
                paths[v].neither += 0
                paths[v].dac += 0
                paths[v].fft += other.neither + other.fft
                paths[v].both += other.both + other.dac
            elif v == "dac":
                paths[v].neither += 0
                paths[v].dac += other.dac + other.neither
                paths[v].fft += 0
                paths[v].both += other.both + other.fft
            else:
                paths[v].neither += other.neither
                paths[v].dac += other.dac
                paths[v].fft += other.fft
                paths[v].both += other.both
    return paths[v]


def solve_part_1(graph: dict[str, list[str]]) -> int:
    rev_graph = rev(graph)
    paths = {}
    return dfs_simple("out", rev_graph, paths)


def solve_part_2(graph: dict[str, list[str]]) -> int:
    rev_graph = rev(graph)
    paths = {}
    return dfs_complex("out", rev_graph, paths).both


start = time.time()
print(f"part 1: {solve_part_1(graph)}")
print(f"part 2: {solve_part_2(graph)}")
end = time.time()
print(f"time: {end - start:.3f}s")
