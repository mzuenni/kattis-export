#!/usr/bin/env python3

n, a, ans = int(input()), list(map(int, input().split())), []


def move(x, y): _, a[x : x + 3], a[y:y] = ans.append((x + 1, y + 1)), [], a[x : x + 3]


for i in range(n - 1, 2, -1):
    idx = a.index(i + 1)
    for _ in range(max(0, 2 - idx)): move(0, 1)
    move(max(2, idx) - 2, i - 2)

# Random moves until success
while a[0:5] != [1, 2, 3, 4, 5]: move(*(__import__("random").randint(0, 2) for _ in ".."))

# At this point all but the first 5 positions are good
print(*([len(ans)] + [" ".join(map(str, xy)) for xy in ans]), sep="\n")
