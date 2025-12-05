import math

part_1 = 0
part_2 = 0
ranges = input().split(",")

for r in ranges:
    (a, b) = r.split("-")
    a = int(a)
    b = int(b)
    for i in range(a, b + 1):
        digits = math.ceil(math.log10(i))
        for j in range(1, digits):
            if digits % j != 0:
                continue
            mod = 10**j
            k = i
            target = k % mod
            good = True
            while k > 0:
                if k % mod != target:
                    good = False
                    break
                k //= mod
            if good:
                part_2 += i
                break

        if digits % 2 == 1:
            pass
        mod = 10 ** (digits // 2)
        if i % mod == i // mod:
            part_1 += i

print(f"part 1: {part_1}")
print(f"part 2: {part_2}")
