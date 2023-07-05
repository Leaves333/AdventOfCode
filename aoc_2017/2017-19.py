maze = []

line = input()
while line != '':
    maze.append(line)
    line = input()

y = 0
x = maze[0].index('|')
direction = 2 # 0 up, 1 right, 2 down, 3 left

def in_bounds(y, x):
    return y >= 0 and x >= 0 and y < len(maze) and x < len(maze[0])

solution_string = ''
steps = 0
while True:

    steps += 1

    if direction == 0:
        y -= 1
    elif direction == 1:
        x += 1
    elif direction == 2:
        y += 1
    elif direction == 3:
        x -= 1

    expected_chars = '-|'

    if maze[y][x] not in expected_chars:
        char = maze[y][x]
        if char == '+':
            if in_bounds(y - 1, x) and maze[y - 1][x] != ' ' and direction % 2 != 0:
                direction = 0
            elif in_bounds(y, x + 1) and maze[y][x + 1] != ' ' and direction % 2 != 1:
                direction = 1
            elif in_bounds(y + 1, x) and maze[y + 1][x] != ' ' and direction % 2 != 0:
                direction = 2
            elif in_bounds(y, x - 1) and maze[y][x - 1] != ' ' and direction % 2 != 1:
                direction = 3
        elif char == ' ':
            break
        else:
            solution_string += maze[y][x]

print(solution_string)
print(steps)

# time: 26:45