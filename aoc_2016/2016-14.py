from copy import deepcopy
import hashlib

keys = []
found = 0
last_index = -1
salt = 'ihaygndm'

index = 0
hashes = []
while found < 64:

    key = salt + str(index)
    result = hashlib.md5(key.encode()).hexdigest()
    for i in range(2016):
        result = hashlib.md5(result.encode()).hexdigest()

    for i in range(len(result) - 4):
        valid = True
        for j in range(5):
            if result[i + j] != result[i]:
                valid = False
        if valid:
            print("found cool hash: " + result)
            for item in deepcopy(keys):
                if result[i] == item[1]:
                    last_index = item[0]
                    keys.remove(item)
                    found += 1
                    hashes.append(item[0])
                    print("found " + str(found) + "/64, key=" + str(item[0]) + ", index=" + str(index))

    for i in range(len(result) - 2):
        triple = True
        for j in range(3):
            if result[i + j] != result[i]:
                triple = False
        if triple:
            keys.append([index, result[i]])
            break

    for item in deepcopy(keys):
        if item[0] + 1000 < index:
            keys.remove(item)
        else:
            break

    index += 1

uwu = sorted(hashes)
print(uwu[63])