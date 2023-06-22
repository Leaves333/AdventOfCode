monkeys = {}

class Monkey():

    def __init__(self, a = None, b = None, op = None, value = None):
        self.a = a
        self.b = b
        self.op = op
        self.num = value

    def value(self):
        if self.num != None:
            return self.num
        self.num = eval(str(monkeys[self.a].value()) + self.op + str(monkeys[self.b].value()))
        return self.num

last_line = input()
while last_line != '':
    p = last_line.split(' ')
    name = p[0][:-1]
    if len(p) == 2:
        monkeys[name] = Monkey(value=int(p[1]))
    else:
       monkeys[name] = Monkey(a=p[1], b=p[3], op=p[2])
    last_line = input()

print(int(monkeys['root'].value()))

path = []
to_check = 'humn'
while to_check != 'root':
    for k in monkeys.keys():
        if monkeys[k].a == to_check or monkeys[k].b == to_check:
            path.append(to_check)
            to_check = k
            break
path.reverse()

static = -1
if monkeys['root'].a not in path:
    static = monkeys[monkeys['root'].a].value()
else:
    static = monkeys[monkeys['root'].b].value()

for p in path:

    if p == 'humn':
        break

    cur_mon = monkeys[p]

    a = -1
    b = -1
    if cur_mon.a not in path:
        a = monkeys[cur_mon.a].value()
    else:
        b = monkeys[cur_mon.b].value()

    #a op b needs to equal static, static is now whatever the undefined one needed to be
    # a + b = static, so a = static - b, b = static - a
    # a - b = static, so a = static + b, b = -1 * (static - a)
    # a * b = static, so a = static / b, b = static / a
    # a / b = static, so a = static * b, b = a / static
    if a == -1:
        if cur_mon.op == '+':
            static = static - b
        elif cur_mon.op == '-':
            static = static + b
        elif cur_mon.op == '*':
            static = static / b
        elif cur_mon.op == '/':
            static = static * b
    else:
        if cur_mon.op == '+':
            static = static - a
        elif cur_mon.op == '-':
            static = -1 * (static - a)
        elif cur_mon.op == '*':
            static = static / a
        elif cur_mon.op == '/':
            static = a / static

print(int(static))