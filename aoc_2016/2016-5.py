import hashlib

key = "cxdnnyjw"
index = 0
ans = "________"

#print(hashlib.md5((key + str(3231929)).encode()).hexdigest())

print("decrypting password...")
print(ans, end="\r")

done = False
while not done:

    done = True
    for i in range(8):
        if (ans[i] == "_"):
            done = False

    found = False
    while not found:
        found = True
        result = hashlib.md5((key + str(index)).encode()).hexdigest()
        index += 1
        for k in range(5):
            if result[k] != "0":
                found = False
        x = result[5]
        if found and (x == "1" or x == "2" or x == "3" or x == "4" or x == "5" or x == "6" or x == "7" or x == "0"):
            #ans += result[5]
            pos = int(x)
            if (ans[pos] == "_"):
                ans = ans[:pos] + result[6] + ans[pos + 1:]
                print(ans, end="\r")

print("decryption complete")
print("password: " + ans)