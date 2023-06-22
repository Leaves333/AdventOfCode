line = input()
one = 0
two = 0

while line != '':
    words = line.split(' ')

    good = True
    for i in range(len(words)):
        for j in range(i + 1, len(words)):
            if words[i] == words[j]:
                good = False
                break
    if good:
        one += 1

    LETTERS = 'qwertyuiopasdfghjklzxcvbnm'
    good = True
    for i in range(len(words)):
        for j in range(i + 1, len(words)):

            first = dict()
            second = dict()
            for c in LETTERS:
                first[c] = 0
                second[c] = 0


            for c in words[i]:
                first[c] += 1
            for c in words[j]:
                second[c] += 1

            anagram = True
            for c in LETTERS:
                if first[c] != second[c]:
                    anagram = False
                    break
            if anagram:
                good = False
                break

    if good:
        two += 1

    line = input()

print(f'part 1: {one}')
print(f'part 2: {two}')

# time: 11:02