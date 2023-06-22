import itertools
import queue
import math

cur_line = input()
rates = {}
valves = {}
valuable_valves = []

while cur_line != '':

    parts = cur_line.split(' ')
    valve_name = parts[1]
    rate = int(parts[4][5:-1])
    leads_to = [k.rstrip(',') for k in parts[9:]]

    rates[valve_name] = rate
    valves[valve_name] = leads_to
    if rate != 0:
        valuable_valves.append(valve_name)

    cur_line = input()

dist_from = {}
dist = {}
q = queue.PriorityQueue()

def search(x):
    for v in valves[x]:
        if v not in dist or dist[x] + 1 < dist[v]:
            dist[v] = dist[x] + 1
            q.put((dist[x] + 1, v))

for i in valuable_valves:

    dist.clear()
    dist[i] = 0
    q.put((0, i))
    while q.qsize() != 0:
        search(q.get()[1])

    dist_from[i] = {}
    for j in valuable_valves:
        dist_from[i][j] = dist[j]

for i in ['AA']: #jank af

    dist.clear()
    dist[i] = 0
    q.put((0, i))
    while q.qsize() != 0:
        search(q.get()[1])

    dist_from[i] = {}
    for j in valuable_valves:
        dist_from[i][j] = dist[j]

max_pressure = 0
k = 0
unvisited = valuable_valves.copy()
last_valve = 'AA'
DEPTH = 6
while k < 30 and len(unvisited) > 0:

    #find ideal pressure per min valve to open
    best_ppm = 0
    best_dist = 0
    best_released = 0
    best_dest = []

    print("at " + last_valve)
    uwu = str(math.factorial(len(unvisited)) / math.factorial(len(unvisited) - DEPTH) // 10000)

    i = 0
    for perm in itertools.permutations(unvisited, min(DEPTH, len(unvisited))):
        if i % 10000 == 0:
            print(str(i//10000) + '/' + uwu, end='\r')
        i += 1

        total_dist = 0
        total_released = 0

        last = last_valve
        for v in perm:
            total_dist += dist_from[last][v] + 1
            if total_dist + k > 30:
                break
            total_released += ((30 - k - total_dist) * rates[v])
            last = v
        
        ppm = total_released / total_dist

        if total_released > best_released:
            best_ppm = ppm
            best_dest = perm
            best_dist = total_dist
            best_released = total_released

        #print(perm, ppm)
    #print()

    k += best_dist
    max_pressure += best_released
    for i in best_dest:
        unvisited.remove(i)
    last_valve = best_dest[-1]

print()
print(max_pressure)