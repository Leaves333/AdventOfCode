class Circuit:
    first: str
    second: str
    operation: str
    output: str

    def __init__(self, first: str, second, operation, output) -> None:
        self.first = first
        self.second = second
        self.operation = operation
        self.output = output

    def __str__(self) -> str:
        return f"[ {self.first} {self.operation} {self.second} -> {self.output} ]"

wire_values: dict[str, int] = dict()
remaining_circuits: list[Circuit] = []

with open("input.txt", "r") as file:
    while True:
        line = file.readline().rstrip("\n")
        if line == "": break
        name, value = line.split(": ")
        wire_values[name] = int(value)
    while True:
        line = file.readline().rstrip("\n")
        if line == "": break
        parts = line.split(" ")
        first, second, operation, output = parts[0], parts[2], parts[1], parts[4]
        remaining_circuits.append(Circuit(first, second, operation, output))

# print([str(x) for x in remaining_circuits])

while len(remaining_circuits) > 0:
    for i in range(len(remaining_circuits) - 1, -1, -1):
        cur = remaining_circuits[i]
        if cur.first not in wire_values or cur.second not in wire_values:
            continue
        remaining_circuits.pop(i)

        if cur.operation == "AND":
            wire_values[cur.output] = wire_values[cur.first] and wire_values[cur.second]
        elif cur.operation == "OR":
            wire_values[cur.output] = wire_values[cur.first] or wire_values[cur.second]
        elif cur.operation == "XOR":
            wire_values[cur.output] = wire_values[cur.first] ^ wire_values[cur.second]


# print("finished evaluating wires")
# print(wire_values)

part_1 = 0
bit = 0
while True:
    key = "z"
    if bit < 10:
        key += "0" + str(bit)
    else:
        key += str(bit)
    if key not in wire_values:
        break
    part_1 += wire_values[key] << bit;
    bit += 1

print(f"part 1: {part_1}")
