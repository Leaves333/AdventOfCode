scanners = dict()

line = input()
while line != '':
    depth, rrange = map(int, line.split(': '))
    scanners[depth] = rrange
    line = input()

pos = dict()
going_up = dict()
for key in scanners.keys():
    pos[key] = 0
    going_up[key] = True

severity = 0
for i in range(max(scanners.keys()) + 1):
    if i in pos.keys() and pos[i] == 0:
        severity += i * scanners[i]
    for j in scanners.keys():
        if going_up[j]:
            pos[j] += 1
            if pos[j] >= scanners[j]:
                going_up[j] = False
                pos[j] -= 2
        else:
            pos[j] -= 1
            if pos[j] < 0:
                going_up[j] = True
                pos[j] += 2

print(severity)

for key in scanners.keys():
    pos[key] = 0
    going_up[key] = True

def position(time, range):
    offset = time % ((range - 1) * 2)
    return offset

delay = 0
found = False
while not found:
    delay += 1
    found = True
    for i in range(max(scanners.keys()) + 1):
        if i in pos.keys() and position(i + delay, scanners[i]) == 0:
            found = False
            break

print(delay)

# time: 21:46