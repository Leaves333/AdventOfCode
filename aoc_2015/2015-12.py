import json

data = []
with open("input.txt") as file:
    data = json.loads(file.read())

total = 0
def f(data):
    global total
    if (isinstance(data, dict)):
        hasRed = False;
        for x in data.values():
            if (x == "red"):
                hasRed = True
        if (not hasRed):
            for z in data.values():
                if (isinstance(z, int)):
                    total += z
                if (isinstance(z, dict) or isinstance(z, list)):
                    f(z)
    elif (isinstance(data, list)):
        for y in data:
            if (isinstance(y, dict) or isinstance(y, list)):
                f(y)
            if (isinstance(y, int)):
                total += y;

f(data)

print(total)