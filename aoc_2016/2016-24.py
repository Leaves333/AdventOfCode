#grab input
nodes = 8
part_two = True

lines = []
cur_line = '69'
while (cur_line != ''):
    cur_line = input()
    lines.append(cur_line)

#identify locations
locations = {}
for i in range(len(lines) - 1):
    for j in range(len(lines[0])):
        if lines[i][j] != '#' and lines[i][j] != '.':
            locations[lines[i][j]] = (i, j)

#do dfs/floodfill to generate graph
min_dist = []
for i in range(len(lines) - 1):
    min_dist.append([])
    for j in range(len(lines[0])):
        min_dist[i].append(100000)

distances = []
for i in range(nodes):
    distances.append([])
    for j in range(nodes):
        distances[i].append(0)

#util functions
def in_bounds(x, y):
    return x > 0 and x < len(lines) - 1 and y > 0 and y < len(lines[0]) and lines[x][y] != '#'

target = 'uwu'
stack = []
def dfs(x, y):

    #search adjacent squares
    if (in_bounds(x + 1, y) and min_dist[x + 1][y] > min_dist[x][y] + 1):
        min_dist[x + 1][y] = min_dist[x][y] + 1
        stack.insert(0, (x + 1, y))

    if (in_bounds(x - 1, y) and min_dist[x - 1][y] > min_dist[x][y] + 1):
        min_dist[x - 1][y] = min_dist[x][y] + 1
        stack.insert(0, (x - 1, y))

    if (in_bounds(x, y + 1) and min_dist[x][y + 1] > min_dist[x][y] + 1):
        min_dist[x][y + 1] = min_dist[x][y] + 1
        stack.insert(0, (x, y + 1))

    if (in_bounds(x, y - 1) and min_dist[x][y - 1] > min_dist[x][y] + 1):
        min_dist[x][y - 1] = min_dist[x][y] + 1
        stack.insert(0, (x, y - 1))

#use dfs to generate distances
for i in range(nodes):

    #reset min_dist array
    for x in range(len(min_dist)):
        for y in range(len(min_dist[0])):
            min_dist[x][y] = 100000

    #generate min_dist array starting from i
    loc = locations[str(i)]
    min_dist[loc[0]][loc[1]] = 0;

    stack.clear()
    stack.append((loc[0], loc[1]))
    while len(stack) > 0:
        top = stack.pop(0)
        dfs(top[0], top[1])
    
    for j in range(i, nodes):
        
        target = str(j)
        target_loc = locations[target]
        distances[i][j] = min_dist[target_loc[0]][target_loc[1]]
        distances[j][i] = min_dist[target_loc[0]][target_loc[1]]
        print(str(i) + " " + str(j) + " " + str(distances[i][j]))

#recursively check all paths
def dist(cur_loc, cur_dist, unvisited):

    best_path = 100000
    
    for i in range(len(unvisited)):
        dest = unvisited.pop(i)
        best_path = min(best_path, dist(dest, cur_dist + distances[int(cur_loc)][int(dest)], unvisited))
        unvisited.insert(i, dest)

    if len(unvisited) == 0:
        if part_two:
            best_path = cur_dist + distances[int(cur_loc)][0]
        else:
            best_path = cur_dist
        
    return best_path

to_visit = []
for i in range(nodes):
    to_visit.append(str(i))
print(dist('0', 0, to_visit))
