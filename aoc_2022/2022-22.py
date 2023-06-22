board = []
cur_line = input()
longest_len = 0
while cur_line != '':
    board.append(cur_line)
    longest_len = max(longest_len, len(cur_line))
    cur_line = input()

for i in range(len(board)):
    board[i] = board[i].ljust(longest_len)

# find initial pos
x = 0
y = 0
for i in range(len(board[0])):
    if board[0][i] != ' ':
        x = i
        break

instructions = input()
direction = 0 # 0 right, 1 down, 2 left, 3 up
while len(instructions) != 0:
    if instructions[0].isdigit():

        r = instructions.find('R')
        if r == -1:
            r = len(instructions)
        l = instructions.find('L')
        if l == -1:
            l = len(instructions)

        num = int(instructions[:min(r, l)])
        instructions = instructions[min(r, l):]

        dx = 0
        dy = 0
        if direction == 0:
            dx = 1
        elif direction == 1:
            dy = 1
        elif direction == 2:
            dx = -1
        else:
            dy = -1

        for i in range(num):
            next_x = x + dx
            next_y = y + dy
            next_x %= len(board[0])
            next_y %= len(board)

            if board[next_y][next_x] == '#':
                break
            elif board[next_y][next_x] == '.':
                x = next_x
                y = next_y
            else:
                while board[next_y][next_x] == ' ':
                    next_x += dx
                    next_y += dy
                    next_x %= len(board[0])
                    next_y %= len(board)
                if board[next_y][next_x] == '#':
                    break
                elif board[next_y][next_x] == '.':
                    x = next_x
                    y = next_y

    else:
        if instructions[0] == 'R':
            direction += 1
        else:
            direction -= 1
        direction %= 4
        instructions = instructions[1:]

print(1000 * (y + 1) + 4 * (x + 1) + direction)