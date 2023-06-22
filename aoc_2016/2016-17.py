import hashlib
import queue

key = "vkjiggvb"
shortest_path = "uwu"
longest_path = "uwu"

q = queue.Queue()

def dfs(path):

    global key, shortest_path, longest_path

    #figure out where you are
    x = 0
    y = 0
    for i in range(len(path)):
        if (path[i] == 'U'):
            y -= 1
        if (path[i] == 'D'):
            y += 1
        if (path[i] == 'R'):
            x += 1
        if (path[i] == 'L'):
            x -= 1

    #check if at final destination
    if x == 3 and y == 3:
        if shortest_path == "uwu":
            shortest_path = path
        elif len(path) < len(shortest_path):
            shortest_path = path
        if longest_path == "uwu":
            longest_path = path
        elif len(path) > len(longest_path):
            longest_path = path
        return

    #generate possible paths and add them to the queue
    result = hashlib.md5((key + path).encode()).hexdigest()
    valid = "bcdef"
    if y > 0 and result[0] in valid:
        q.put(path + "U")
    if y < 3 and result[1] in valid:
        q.put(path + "D")
    if x > 0 and result[2] in valid:
        q.put(path + "L")
    if x < 3 and result[3] in valid:
        q.put(path + "R")

q.put('')
while not q.empty():
    dfs(q.get())

print(shortest_path)
print(len(longest_path))