weights = dict()
edges = dict()

line = input()
while line != '':

    info = line.split()
    name = info[0]
    weight = int(info[1][1:-1])
    weights[name] = weight
    edges[name] = []

    if len(info) > 2:
        for i in range(3, len(info)):
            dest = info[i]
            if i != len(info) - 1:
                dest = dest[:-1]
            edges[name].append(dest)

    line = input()

visited = set()
def dfs(position):
    visited.add(position)
    for dest in edges[position]:
        if dest not in visited:
            dfs(dest)

root = ''
for start in edges.keys():
    visited.clear()
    dfs(start)
    if len(visited) == len(edges.keys()):
        print(f'part 1: {start}')
        root = start
        break

total_weight = dict()
def calculate_weight(pos):
    total_weight[pos] = weights[pos]
    for dest in edges[pos]:
        total_weight[pos] += calculate_weight(dest)
    return total_weight[pos]

calculate_weight(root)

diff = 0
def find_wrong_weight(pos):

    weight_freq = dict()
    for dest in edges[pos]:
        if total_weight[dest] not in weight_freq.keys():
            weight_freq[total_weight[dest]] = 0
        weight_freq[total_weight[dest]] += 1

    global diff
    if len(weight_freq.keys()) > 1:

        wrong_weight = 0
        right_weight = 0
        for key in weight_freq.keys():
            if weight_freq[key] == 1:
                wrong_weight = key
            else:
                right_weight = key
        diff = right_weight - wrong_weight

        for dest in edges[pos]:
            if weight_freq[total_weight[dest]] == 1:
                find_wrong_weight(dest)
                break
    
    else:
        print(f'part 2: {weights[pos] + diff}')

find_wrong_weight(root)

# time: 27:23