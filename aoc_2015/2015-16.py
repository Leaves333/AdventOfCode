from turtle import right


target = {}

with open("input.txt") as file:
    for i in range(10):
        line = file.readline().split(" ")
        line[0] = line[0].rstrip(":")
        target[line[0]] = int(line[1].rstrip("\n"))

    for i in range(500):
        line = file.readline().split(" ")
        right_person = True

        line[1] = line[1].rstrip(":")
        line[2] = line[2].rstrip(":")
        line[3] = line[3].rstrip(",")
        line[4] = line[4].rstrip(":")
        line[5] = line[5].rstrip(",")
        line[6] = line[6].rstrip(":")
        line[7] = line[7].rstrip("\n")

        if target[line[2]] != int(line[3]):
            right_person = False
        if target[line[4]] != int(line[5]):
            right_person = False
        if target[line[6]] != int(line[7]):
            right_person = False
        if right_person:
            print("part 1: " + line[1])

        right_person = True
        for j in range(2, 7, 2):
            if (line[j] == "cats" or line[j] == "trees"):
                if (target[line[j]] >= int(line[j + 1])):
                    right_person = False
            elif (line[j] == "pomeranians" or line[j] == "goldfish"):
                if (target[line[j]] <= int(line[j + 1])):
                    right_person = False
            elif (target[line[j]] != int(line[j + 1])):
                right_person = False
        if right_person:
            print("part 2: " + line[1])
