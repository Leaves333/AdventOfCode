import itertools
import collections
import copy
import queue
import heapq

start = [
    ['E', 'e', 'F', 'f', 'G', 'g'],
    ['A', 'B', 'C', 'D'],
    ['a', 'b', 'c', 'd'],
    []
]

#start = [
#    ['a', 'b'],
#    ['A'],
#    ['B'],
#    []
#]

ans = int(1000)
previous_states = [[], [], [], []]
q = []
heapq.heappush(q, (0, (start, 0, 0)))
k = 0

def h(board):
    return 2 * (3 * len(board[0]) + 2 * len(board[1]) + len(board[2]))

def iterate(board, floor, move):

    global k
    k += 1
    if k % 1000 == 0:
        print("k=" + str(k) + " \tmove=" + str(move) + " \tqueueSize=" + str(len(q)))
    
    #check that solution is actually better
    global ans
    if move >= ans:
        return

    #prune out illegal board states
    for f in board:
        if 'A' in f or 'B' in f or 'C' in f or 'D' in f or 'E' in f:
            if 'a' in f and not 'A' in f:
                return
            if 'b' in f and not 'B' in f:
                return
            if 'c' in f and not 'C' in f:
                return
            if 'd' in f and not 'D' in f:
                return
            if 'e' in f and not 'E' in f:
                return
    

    #check for final board state
    if len(board[0]) + len(board[1]) + len(board[2]) == 0:
        ans = min(ans, move)
        print("answer: " + str(move))
        return

    #remember visited board states
    occurred_previously = False
    for state in previous_states[floor]:
        has_occurred = True
        status = []
        for i in range(len(board)):
            upper = 0
            lower = 0
            for item in board[i]:
                if item.isupper():
                    upper += 1
                elif item.islower():
                    lower += 1
            status.append((upper, lower))
        if state != status:
            has_occurred = False
        if has_occurred:
            occurred_previously = True

    if not occurred_previously:
        status = []
        for i in range(len(board)):
            upper = 0
            lower = 0
            for item in board[i]:
                if item.isupper():
                    upper += 1
                elif item.islower():
                    lower += 1
            status.append((upper, lower))
        previous_states[floor].append(copy.deepcopy(status))
    else:
        return

    #print(board)
    #print(floor)
    #print(move)
    #print()

    if (len(board[floor]) >= 2):
        for item in itertools.combinations(board[floor], 2):
            empty_below = True
            for i in range(floor):
                if len(board[i]) != 0:
                    empty_below = False
            if (floor > 0 and not empty_below):
                new_board = copy.deepcopy(board)
                new_board[floor].remove(item[0])
                new_board[floor].remove(item[1])
                new_board[floor - 1].append(item[0])
                new_board[floor - 1].append(item[1])
                heapq.heappush(q, (move + h(new_board), (new_board, floor - 1, move + 1)))
                #q.put((new_board, floor - 1, move + 1))
                #iterate(new_board, floor - 1, move + 1)
            if (floor < 3):
                new_board = copy.deepcopy(board)
                new_board[floor].remove(item[0])
                new_board[floor].remove(item[1])
                new_board[floor + 1].append(item[0])
                new_board[floor + 1].append(item[1])
                heapq.heappush(q, (move + h(new_board), (new_board, floor + 1, move + 1)))
                #q.put((new_board, floor + 1, move + 1))
                #iterate(new_board, floor + 1, move + 1)
    
    for item in board[floor]:
        empty_below = True
        for i in range(floor):
            if len(board[i]) != 0:
                empty_below = False
        if (floor > 0 and not empty_below):
            new_board = copy.deepcopy(board)
            new_board[floor].remove(item)
            new_board[floor - 1].append(item)
            heapq.heappush(q, (move + h(new_board), (new_board, floor - 1, move + 1)))
            #q.put((new_board, floor - 1, move + 1))
            #iterate(new_board, floor - 1, move + 1)
        if (floor < 3):
            new_board = copy.deepcopy(board)
            new_board[floor].remove(item)
            new_board[floor + 1].append(item)
            heapq.heappush(q, (move + h(new_board), (new_board, floor + 1, move + 1)))
            #q.put((new_board, floor + 1, move + 1))
            #iterate(new_board, floor + 1, move + 1)

while len(q) != 0:
    item = heapq.heappop(q)
    item = item[1]
    iterate(item[0], item[1], item[2])

print("uwu")
print(ans)
print("done")