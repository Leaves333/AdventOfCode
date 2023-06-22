import copy

previous_configs = []
nums = list(map(int, input().split()))

cycles = 0
while nums not in previous_configs:
    previous_configs.append(copy.copy(nums))

    lowest_index = 0
    for i in range(1, len(nums)):
        if (nums[i] > nums[lowest_index]):
            lowest_index = i

    to_distribute = nums[lowest_index]
    nums[lowest_index] = 0
    for i in range(lowest_index + 1, to_distribute + lowest_index + 1):
        nums[i % len(nums)] += 1

    cycles += 1

print(f'part 1: {cycles}')
print(f'part 2: {cycles - previous_configs.index(nums)}')

# time: 8:28