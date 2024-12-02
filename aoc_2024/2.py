def good_list(nums: list) -> bool:
    increasing = nums[1] > nums[0]
    good = True
    for i in range(1, len(nums)):
        diff = nums[i] - nums[i - 1]
        if abs(diff) > 3 or abs(diff) < 1:
            good = False
            break
        if diff > 0 and (not increasing) or diff < 0 and increasing:
            good = False
            break
    return good

with open("input.txt", "r") as file:
    part_1 = 0
    part_2 = 0
    while True:
        line = file.readline()
        if not line: break
        nums = list(map(int, line.split()))
        if good_list(nums):
            part_1 += 1

        for i in range(len(nums)):
            new_nums = nums.copy()
            new_nums.pop(i)
            if good_list(new_nums):
                part_2 += 1
                break

    print(f"part 1: {part_1}")
    print(f"part 2: {part_2}")
