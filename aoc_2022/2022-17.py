STREAM = input()
NUM = 1000000000000 #adjust this to how many rocks you're trying to calculate
HEIGHT_LIM = 50000 #adjust this if out of bounds
t_list = []
cycle_len = 1755 #find it yourself from the txt file lol

def height(num_rocks):

    rocks = [[False for i in range(HEIGHT_LIM)] for i in range(7)]
    for i in range(7):
        rocks[i][0] = True

    max_height = 1
    t = 0

    for k in range(num_rocks):

        falling_rocks = []
        if k % 5 == 0:
            falling_rocks.append([2, max_height + 3])
            falling_rocks.append([3, max_height + 3])
            falling_rocks.append([4, max_height + 3])
            falling_rocks.append([5, max_height + 3])
        elif k % 5 == 1:
            falling_rocks.append([2, max_height + 4])
            falling_rocks.append([3, max_height + 3])
            falling_rocks.append([3, max_height + 4])
            falling_rocks.append([3, max_height + 5])
            falling_rocks.append([4, max_height + 4])
        elif k % 5 == 2:
            falling_rocks.append([2, max_height + 3])
            falling_rocks.append([3, max_height + 3])
            falling_rocks.append([4, max_height + 3])
            falling_rocks.append([4, max_height + 4])
            falling_rocks.append([4, max_height + 5])
        elif k % 5 == 3:
            falling_rocks.append([2, max_height + 3])
            falling_rocks.append([2, max_height + 4])
            falling_rocks.append([2, max_height + 5])
            falling_rocks.append([2, max_height + 6])
        elif k % 5 == 4:
            falling_rocks.append([2, max_height + 3])
            falling_rocks.append([2, max_height + 4])
            falling_rocks.append([3, max_height + 3])
            falling_rocks.append([3, max_height + 4])

        while True:

            dx = 0
            if STREAM[t] == '>':
                dx = 1
            else:
                dx = -1

            t += 1
            t %= len(STREAM)

            good = True
            for r in falling_rocks:
                if r[0] + dx >= 7 or r[0] + dx < 0 or rocks[r[0] + dx][r[1]]:
                    good = False
                    break
            if good:
                for r in falling_rocks:
                    r[0] += dx

            good = True
            for r in falling_rocks:
                if rocks[r[0]][r[1] - 1]:
                    good = False
                    break
            if good:
                for r in falling_rocks:
                    r[1] -= 1
            else:
                break

        for r in falling_rocks:
            rocks[r[0]][r[1]] = True
        
        for i in range(max_height, HEIGHT_LIM):
            found = False
            for j in range(7):
                if rocks[j][i]:
                    max_height = i + 1
                    found = True
                    break
            if not found:
                break
        
        global t_list
        t_list.append(t)

    return max_height - 1

height(20000)
with open("dump.txt", "w") as file:
    for i in t_list:
        file.write(str(i) + "\n")

diff = height(4 * cycle_len) - height(3 * cycle_len)
base = height(cycle_len)
mid = (NUM // cycle_len - 1) * diff
end = height(NUM % cycle_len + cycle_len) - height(cycle_len)
print(base + mid + end)
#print(base, mid, end)