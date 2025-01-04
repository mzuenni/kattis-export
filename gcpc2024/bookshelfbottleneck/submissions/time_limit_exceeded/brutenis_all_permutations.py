import sys
from itertools import permutations
sys.setrecursionlimit(10000000)

n, shelf_height = map(int, input().split())

best = 1e100
books = []

def find(index, score):
    global best
    if index == len(books):
        best = min(best, score)
        return
    for height, width, _ in permutations(books[index]):
        if height <= shelf_height:
            find(index+1, score+width)

for _ in range(n):
    books.append([int(a) for a in input().split()])

find(0, 0)

print(best if best != 1e100 else "impossible")
