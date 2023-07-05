spin = int(input())

buffer = [0]
pos = 0
for i in range(2017):
    pos += spin
    pos %= len(buffer)
    buffer.insert(pos + 1, i + 1)
    pos += 1
print(buffer[(pos + 1) % len(buffer)])

pos = 0
ans = 0
for i in range(50000000):
    pos += spin
    pos %= i + 1
    if pos == 0:
        ans = i + 1
    pos += 1

print(ans)

# time: 12:49