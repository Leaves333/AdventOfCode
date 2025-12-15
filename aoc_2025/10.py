from queue import PriorityQueue
import pulp
import time

INF = 10**20


class Machine:
    def __init__(
        self, n: int, target: int, buttons: list[int], joltages: list[int]
    ) -> None:
        self.n = n
        self.target = target
        self.buttons = buttons
        self.joltages = joltages

    def __str__(self) -> str:
        return f"Machine: (target: {self.target}, buttons: {self.buttons}, joltages: {self.joltages})"

    def solve_p1(self) -> int:
        """returns the minimum number of button presses needed to solve"""

        dist: list[int] = [INF for _ in range(2**self.n)]
        pq: PriorityQueue[tuple[int, int]] = PriorityQueue()  # stores (dist, state)
        pq.put((0, 0))
        dist[0] = 0

        while not pq.empty():
            (cur_dist, cur) = pq.get()
            for b in self.buttons:
                dest = cur ^ b
                if dist[dest] > cur_dist + 1:
                    dist[dest] = cur_dist + 1
                    pq.put((cur_dist + 1, dest))

        # print(f"solve for {bin(self.target): >15} returned {dist[self.target]}")
        return dist[self.target]

    def solve_p2(self) -> int:
        """returns the minimum number of button presses needed to solve"""

        # create the linear programming problem
        prob = pulp.LpProblem("PresentsProblemV2", pulp.LpMinimize)

        # create a variable for each coefficient
        vars = [
            pulp.LpVariable(f"a_{i}", 0, None, cat=pulp.LpInteger)
            for i in range(len(self.buttons))
        ]

        # define the vectors
        vectors: list[list[int]] = []
        for mask in self.buttons:
            v = [0 for _ in range(len(self.joltages))]
            for i in range(len(self.joltages)):
                if mask & (2**i):
                    v[i] = 1
            vectors.append(v)

        # objective function is sum of all coefficients
        prob += pulp.lpSum(vars)

        # constraints are that product of vectors and coefficients need to sum to joltages
        for i in range(len(self.joltages)):
            prob += (
                pulp.lpSum([vectors[j][i] * vars[j] for j in range(len(self.buttons))])
                == self.joltages[i]
            )

        prob.solve(pulp.PULP_CBC_CMD(msg=False))
        answer = int(pulp.value(prob.objective))
        print(answer)
        return answer


def solve_part_1(machines: list[Machine]) -> int:
    return sum([m.solve_p1() for m in machines])


def solve_part_2(machines: list[Machine]) -> int:
    return sum([m.solve_p2() for m in machines])


machines: list[Machine] = []
line = input()
while line != "":
    tokens = line.split()

    target_str = tokens[0][1:-1]
    target = 0
    for i in range(len(target_str)):
        if target_str[i] == "#":
            target |= 2**i

    joltages_str = tokens[-1][1:-1]
    joltages = list(map(int, joltages_str.split(",")))

    buttons = []
    for i in range(1, len(tokens) - 1):
        button_str = tokens[i][1:-1]
        button_mask = 0
        for x in map(int, button_str.split(",")):
            button_mask |= 2**x
        buttons.append(button_mask)

    machines.append(Machine(len(target_str), target, buttons, joltages))
    line = input()

start = time.time()
print(f"part 1: {solve_part_1(machines)}")
print(f"part 2: {solve_part_2(machines)}")
end = time.time()
print(f"time: {end - start:.3f}s")
