nums = [x for x in range(256)]
inp = input()
lengths = []
if len(inp.split(',')) > 1:
    lengths = list(map(int, inp.split(',')))

skip = 0
pos = 0
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

print(nums[0] * nums[1])

### part 2 ###
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
print(output)

# time: 38:05