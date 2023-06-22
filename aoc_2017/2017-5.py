PART_1 = False

num = input()
offsets = []
while num != '':
    offsets.append(int(num))
    num = input()

pos = 0
operations = 0
while pos >= 0 and pos < len(offsets):
    if PART_1:
        offsets[pos] += 1
        pos += offsets[pos] - 1
    else:
        original_offset = offsets[pos]
        if offsets[pos] >= 3:
            offsets[pos] -= 1
        else:
            offsets[pos] += 1
        pos += original_offset
    operations += 1

print(f'answer: {operations}')

# time 6:47