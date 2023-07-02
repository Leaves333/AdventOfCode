import sys
sys.setrecursionlimit(10000)

def knot_hash(inp):
    nums = [x for x in range(256)]
    lengths = [ord(inp[i]) for i in range(len(inp))]
    lengths.extend([17, 31, 73, 47, 23])

    skip = 0
    pos = 0
    for t in range(64):
        for k in lengths:
            
            indices = []
            sub = []
            for i in range(k):
                indices.append((pos + i) % len(nums))
                sub.append(nums[(pos + i) % len(nums)])
            sub.reverse()
            for i in range(k):
                nums[indices[i]] = sub[i]

            pos += skip + k
            pos %= len(nums)
            skip += 1

    dense = []
    for i in range(16):
        xor = 0
        for j in range(16):
            xor ^= nums[(i * 16) + j]
        dense.append(xor)

    output = ''
    for k in dense:
        if k < 16:
            output += '0'
        output += hex(k)[2:]
    return output

grid = []
one = 0
key = input()
for i in range(128):
    to_hash = key + '-' + str(i)
    kh = knot_hash(to_hash)
    num = int(kh, 16)
    binary = f'{num:0>128b}'

    line = []
    for k in binary:
        if k == '1':
            one += 1
    grid.append(binary)

visited = [[False for x in range(128)] for x in range(128)]
two = 0
def dfs(x, y):
    visited[x][y] = True
    if x + 1 < 128 and not visited[x + 1][y] and grid[x + 1][y] == '1':
        dfs(x + 1, y)
    if x - 1 >= 0 and not visited[x - 1][y] and grid[x - 1][y] == '1':
        dfs(x - 1, y)
    if y + 1 < 128 and not visited[x][y + 1] and grid[x][y + 1] == '1':
        dfs(x, y + 1)
    if y - 1 >= 0 and not visited[x][y - 1] and grid[x][y - 1] == '1':
        dfs(x, y - 1)

for i in range(128):
    for j in range(128):
        if not visited[i][j] and grid[i][j] == '1':
            two += 1
            dfs(i, j)

print(one)
print(two)

# time: 25:03