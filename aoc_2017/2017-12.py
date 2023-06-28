edges = dict()

line = input()
while line != '':
    line = line.split(' ')
    
    start = int(line[0])
    edges[start] = []
    for k in range(2, len(line)):
        num = line[k]
        dest = -1
        if k != len(line) - 1:
            dest = int(num[:-1])
        else:
            dest = int(num)
        edges[start].append(dest)

    line = input()

connected = 0
visited = set()
def dfs(x):
    visited.add(x)
    global connected
    connected += 1
    for dest in edges[x]:
        if dest not in visited:
            dfs(dest)
dfs(0)

two = 0
visited.clear()
for i in range(2000):
    if i not in visited:
        dfs(i)
        two += 1

print(connected)
print(two)

# time: 9:01