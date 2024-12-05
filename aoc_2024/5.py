edges: list[list[int]] = []
part_1 = 0
part_2 = 0

with open("input.txt", "r") as file:

    # store all the ordering rules in edges
    line = file.readline().rstrip("\n")
    while line != "":
        first, second = map(int, line.split("|"))
        edges.append([first, second])
        line = file.readline().rstrip("\n")

    line = file.readline().rstrip("\n")
    while line:

        nums = list(map(int, line.split(",")))

        # figure out which rules we care about
        prereqs: dict[int, set[int]] = dict()
        for edge in edges:
            if edge[0] not in nums or edge[1] not in nums:
                continue
            if edge[1] not in prereqs:
                prereqs[edge[1]] = set()
            prereqs[edge[1]].add(edge[0])

        # check if list is good
        visited: set[int] = set()
        good = True
        for n in nums:
            if n in prereqs:
                for r in prereqs[n]:
                    if r not in visited:
                        good = False
            visited.add(n)
        
        if good:
            part_1 += nums[len(nums) // 2]
        else:
            sorted_list = []
            visited.clear()

            # repeatedly iterate through nums, checking if we can add the new
            # page to the end of sorted_list
            while len(sorted_list) < len(nums):
                for n in nums:
                    if n in sorted_list:
                        continue
                    can_add = True
                    if n in prereqs:
                        for r in prereqs[n]:
                            if r not in visited:
                                can_add = False
                    if can_add:
                        sorted_list.append(n);
                        visited.add(n)
            part_2 += sorted_list[len(nums) // 2]

        line = file.readline().rstrip("\n")

    print(f"part 1: {part_1}")
    print(f"part 2: {part_2}")
