from queue import Queue

# helper class
class Node():
    depth: int
    starting_node: bool
    out_edges: list[int]

    def __init__(self) -> None:
        self.depth = 0
        self.starting_node = True
        self.out_edges = []

# main program
with open("input.txt", "r") as file:

    # read input and build the graph
    line = file.readline().rstrip("\n")
    nodes: list[Node] = [Node() for _ in range(100)] # inputs are all <= 99

    while line != "":
        first, second = map(int, line.split("|"))
        nodes[first].out_edges.append(second)
        nodes[second].starting_node = False
        line = file.readline().rstrip("\n")

    # calculate the depth of each node
    for i in range(100):
        if not nodes[i].starting_node:
            continue

        queue: Queue[int] = Queue()
        queue.put(i)
        while queue.qsize != 0:
            top = queue.get()
            for dest in nodes[top].out_edges:
                if nodes[dest].depth < nodes[top].depth + 1:
                    nodes[dest].depth = nodes[top].depth + 1
                    queue.put(dest)

    # solve the problem
    line = file.readline().rstrip("\n")
    part_1 = 0
    part_2 = 0
    while line:

        nums = list(map(int, line.split(",")))

        # check if the list is good
        last_depth = nodes[nums[0]].depth
        good_list = True
        for i in range(1, len(nums)):
            cur_depth = nodes[nums[i]].depth
            if cur_depth < last_depth:
                good_list = False
                break
            last_depth = cur_depth

        if good_list:
            part_1 += nums[len(nums) // 2]
            continue

        # fix the list if bad
        nums.sort(key=lambda x: nodes[x].depth)
        part_2 += nums[len(nums) // 2]

        line = file.readline().rstrip("\n")

    print(f"part 1: {part_1}")
    print(f"part 2: {part_2}")
