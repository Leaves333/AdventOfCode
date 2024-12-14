WIDTH = 101
HEIGHT = 103

positions: list[tuple[int, int]] = []
velocities: list[tuple[int, int]] = []
with open("input.txt", "r") as file:
    lines = file.read().split("\n")
    for line in lines:
        if not line: break
        parts = line.split()
        parts[0] = parts[0][parts[0].find("=")+1:]
        parts[1] = parts[1][parts[1].find("=")+1:]

        a, b = map(int, parts[0].split(","))
        positions.append((a, b))
        a, b = map(int, parts[1].split(","))
        velocities.append((a, b))

final_positions: list[tuple[int, int]] = []
for i in range(len(positions)):
    final_x = (positions[i][0] + (100 * velocities[i][0])) % WIDTH
    final_y = (positions[i][1] + (100 * velocities[i][1])) % HEIGHT
    final_positions.append((final_x, final_y))

quadrant_count = [0 for _ in range(4)]
mid_x = WIDTH // 2
mid_y = HEIGHT // 2
for pos in final_positions:
    if pos[0] < mid_x and pos[1] < mid_y:
        quadrant_count[0] += 1
    elif pos[0] > mid_x and pos[1] < mid_y:
        quadrant_count[1] += 1
    elif pos[0] < mid_x and pos[1] > mid_y:
        quadrant_count[2] += 1
    elif pos[0] > mid_x and pos[1] > mid_y:
        quadrant_count[3] += 1

part_1 = quadrant_count[0]
for i in range(1, 4):
    part_1 *= quadrant_count[i]

print(f"part 1: {part_1}")

mut_positions: list[list[int]] = [[] for _ in range(len(positions))]
for i in range(len(positions)):
    mut_positions[i] = list(positions[i])

multiples = []
for i in range(10000):
    if i % 101 == 82 or i % 103 == 47:
        multiples.append(i)

with open("output.txt", "w") as file:
    last = 0
    for t in multiples:
        for i in range(len(positions)):
            mut_positions[i][0] += velocities[i][0] * (t - last)
            mut_positions[i][0] %= WIDTH
            mut_positions[i][1] += velocities[i][1] * (t - last)
            mut_positions[i][1] %= HEIGHT
        last = t
        file.write(f"second: {t}\n")
        for i in range(HEIGHT):
            to_print = ""
            for j in range(WIDTH):
                found = False
                for pos in mut_positions:
                    if pos[0] == j and pos[1] == i:
                        to_print += '#'
                        found = True
                        break
                if not found:
                    to_print += '.'
            file.write(to_print + "\n")
        file.write("\n")
