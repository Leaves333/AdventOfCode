with open("input.txt", "r") as file:
    part_1 = 0
    part_2 = 0
    line = file.readline()
    while line:
        parts = line.split(": ")
        target = int(parts[0])
        nums = list(map(int, parts[1].split(" ")))

        for x in range(2 ** (len(nums) - 1)):
            cur = nums[0]
            for i in range(1, len(nums)):
                if x & 1 << (i - 1):
                    cur += nums[i]
                else:
                    cur *= nums[i]
            if cur == target:
                part_1 += target
                break

        possibilities: set[int] = set()
        possibilities.add(nums[0])
        for i in range(1, len(nums)):
            for x in possibilities.copy():
                add = x + nums[i]
                mult = x * nums[i]
                cat = int(str(x) + str(nums[i]))
                if add <= target:
                    possibilities.add(add)
                if mult <= target:
                    possibilities.add(mult)
                if cat <= target:
                    possibilities.add(cat)
            if target in possibilities:
                part_2 += target
                break

        line = file.readline()

    print(f"part 1: {part_1}")
    print(f"part 2: {part_2}")
