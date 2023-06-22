line = input()
ans = 0
two = 0
while line != '':

    nums = list(map(int, line.split()))
    ans += max(nums) - min(nums)

    for i in range(len(nums)):
        for j in range(i + 1, len(nums)):
            if nums[i] % nums[j] == 0:
                two += int(nums[i] / nums[j])
                break
            if nums[j] % nums[i] == 0:
                two += int(nums[j] / nums[i])
                break

    line = input()

print(f'part 1: {ans}')
print(f'part 2: {two}')

# time to solve: 5:42