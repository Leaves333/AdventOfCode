with open("input.txt", "r") as file:
    lines = file.read()
    lines = lines.split("\n")

part_1 = 0
part_2 = 0
DIFF = 10000000000000

def solve(buttons: list[tuple[int, int]], x: int, y: int) -> int:
    a = buttons[0][0]; b = buttons[0][1]
    i = buttons[1][0]; j = buttons[1][1]

    num = (y * a) - (b * x)
    denom = (j * a) - (i * b)
    if num % denom != 0:
        return -1

    n = num // denom

    num = x - (n * i)
    if num % a != 0:
        return -1

    m = num // a
    if m < 0 or n < 0:
        return - 1
    return (3 * m) + n
    
buttons: list[tuple[int, int]] = []
for i in range(len(lines)):
    if i % 4 == 3: continue

    # location, calc
    if i % 4 == 2:
        text = lines[i].split(": ")[1]
        prize = text.split(", ")
        prize_x = int(prize[0][prize[0].find("=")+1:])
        prize_y = int(prize[1][prize[1].find("=")+1:])

        cost = solve(buttons, prize_x, prize_y)
        if cost != -1:
            part_1 += cost
        cost = solve(buttons, prize_x + DIFF, prize_y + DIFF)
        if cost != -1:
            part_2 += cost

        buttons.clear()
        continue

    # button
    text = lines[i].split(": ")[1]
    changes = text.split(", ")
    x = int(changes[0][2:])
    y = int(changes[1][2:])
    buttons.append((x, y))

print(f"part 1: {part_1}")
print(f"part 2: {part_2}")
