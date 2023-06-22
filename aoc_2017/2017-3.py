import math
loc = int(input())
side_length = math.ceil(math.sqrt(loc))
if side_length % 2 == 0:
    side_length += 1

overflow = int(loc - math.pow(side_length - 2, 2)) - 1
pos_y = (int(side_length / 2) - 1) * -1
pos_x = int(side_length / 2)

dist_up = min(side_length - 2, overflow)
pos_y += dist_up
overflow -= dist_up

dist_left = min(side_length - 1, overflow)
pos_x -= dist_left
overflow -= dist_left

dist_down = min(side_length - 1, overflow)
pos_y -= dist_down
overflow -= dist_down

dist_right = min(side_length - 1, overflow)
pos_x += dist_right
overflow -= dist_right

print(f'part 1: {abs(pos_x)}')

grid = [[0 for x in range(2000)] for x in range(2000)]
x = 1000
y = 1000
grid[x][y] = 1
last_val = 1
direction = 0

while (last_val <= loc):
    if direction % 4 == 0:
        x += 1
        if grid[x][y + 1] == 0:
            direction += 1
    elif direction % 4 == 1:
        y += 1
        if grid[x - 1][y] == 0:
            direction += 1
    elif direction % 4 == 2:
        x -= 1
        if grid[x][y - 1] == 0:
            direction += 1
    elif direction % 4 == 3:
        y -= 1
        if grid[x + 1][y] == 0:
            direction += 1

    last_val = 0
    for i in range(-1, 2):
        for j in range(-1, 2):
            if i == 0 and j == 0:
                continue
            last_val += grid[x + i][y + j]

    grid[x][y] = last_val

print(f'part 2: {last_val}')

# time to solve: 22:06