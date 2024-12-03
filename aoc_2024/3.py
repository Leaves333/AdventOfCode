with open("input.txt", "r") as file:
    part_1 = 0
    part_2 = 0
    do_multiply = True
    while True:

        line = file.readline()
        if not line: break
        
        idx = 0
        while idx != -1:

            idx_do = line.find("do()", idx)
            idx_dont = line.find("don't()", idx)
            idx_mult = line.find("mul", idx)

            if idx_do == -1:
                idx_do = 1000000
            if idx_dont == -1:
                idx_dont = 1000000
            if idx_mult == -1:
                idx_mult = 1000000

            print("")
            print(f"idx_do={idx_do}")
            print(f"idx_dont={idx_dont}")
            print(f"idx_mult={idx_mult}")

            if idx_do < idx_dont and idx_do < idx_mult:
                do_multiply = True
                idx = idx_do + 1
                print(f"do at idx={idx}")
                continue
            
            elif idx_dont < idx_do and idx_dont < idx_mult:
                do_multiply = False
                idx = idx_dont + 1
                print(f"don't at idx={idx}")
                continue

            idx = line.find("mul", idx)
            print(f"here's idx: {idx}, multiplying={do_multiply}")

            if idx == -1:
                break
            idx += 1

            left_paren = line.find("(", idx)
            right_paren = line.find(")", idx)
            print(f"left_paren={left_paren}, right_paren={right_paren}")

            if left_paren == -1 or right_paren == -1 or left_paren != idx + 2:
                continue
            
            contents = line[left_paren+1:right_paren]
            print(f"idx={idx}, contents={contents}")

            args = contents.split(",")
            if len(args) != 2:
                continue
            
            good_nums = True
            for num in args:
                for char in num:
                    if not char.isdigit():
                        good_nums = False;
                        break

            if good_nums:
                part_1 += int(args[0]) * int(args[1])
                if do_multiply:
                    part_2 += int(args[0]) * int(args[1])

    print(f"part 1: {part_1}")
    # correct answer for part 1: 165225049
    print(f"part 2: {part_2}")
