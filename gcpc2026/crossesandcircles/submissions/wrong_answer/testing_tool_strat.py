import random
R = 59
C = 42
OUTSIDE = -2
EMPTY = 0
TEAM = 1
JURY = -1
DIRECTIONS = ((1, 0), (0, 1), (1, 1), (1, -1))
NEIGHBORS = (
    (-1, -1), (-1, 0), (-1, 1),
    (0, -1), (0, 1),
    (1, -1), (1, 0), (1, 1),
)

board = [[EMPTY for _ in range(C)] for _ in range(R)]

def valid(cell):
    row, col = cell
    return 1 <= row <= R and 1 <= col <= C

def value(cell):
    row, col = cell
    if not valid(cell):
        return OUTSIDE
    return board[row - 1][col - 1]

def set_value(cell, player):
    row, col = cell
    board[row - 1][col - 1] = player

def threats(player):
    ans = set()
    for row in range(1, R + 1):
        for col in range(1, C + 1):
            cell = (row, col)
            if value(cell) != EMPTY:
                continue
            for drow, dcol in DIRECTIONS:
                for i, j in ((-2, -1), (-1, 1), (1, 2)):
                    if (
                        value((row + i * drow, col + i * dcol)) == player
                        and value((row + j * drow, col + j * dcol)) == player
                    ):
                        ans.add(cell)
    return ans

def adjacent_empty_cells():
    ans = set()
    for row in range(1, R + 1):
        for col in range(1, C + 1):
            if value((row, col)) == EMPTY:
                continue
            for drow, dcol in NEIGHBORS:
                cell = (row + drow, col + dcol)
                if value(cell) == EMPTY:
                    ans.add(cell)
    return ans

print(9, 9)
set_value((9, 9), TEAM)
while True:
    jury_move = tuple(map(int, input().split()))
    row, col = jury_move
    if not row:
        break
    set_value(jury_move, JURY)
    move = threats(TEAM).pop() if threats(TEAM) else random.choice(list(adjacent_empty_cells()))
    print(*move)
    set_value(move, TEAM)
