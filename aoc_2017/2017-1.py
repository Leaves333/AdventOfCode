num = input("enter your input: ")
ans = 0
for i in range(len(num) - 1):
    if num[i] == num[i + 1]:
        ans += int(num[i])
if num[0] == num[-1]:
    ans += int(num[0])

print(f'part 1: {ans}')

ans = 0
half = len(num) / 2
for i in range(len(num)):
    if num[i] == num[int((i + half) % len(num))]:
        ans += int(num[i])

print(f'part 2: {ans}')