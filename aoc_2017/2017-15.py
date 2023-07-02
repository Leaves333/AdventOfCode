a = 883
b = 879

A_FACTOR = 16807
B_FACTOR = 48271
MOD = 2147483647
SIXTEEN_BITS = 65536

one = 0
a_list = []
b_list = []
for i in range(40000000):
    a *= A_FACTOR
    b *= B_FACTOR
    a %= MOD
    b %= MOD

    if a % 4 == 0:
        a_list.append(a)
    if b % 8 == 0:
        b_list.append(b)

    if (a % SIXTEEN_BITS == b % SIXTEEN_BITS):
        one += 1

two = 0
for i in range(min(len(a_list), len(b_list))):
    if a_list[i] % SIXTEEN_BITS == b_list[i] % SIXTEEN_BITS:
        two += 1

print(one)
print(two)

# time: 10:59