#!/usr/bin/env python3
n, k, q = map(int, input().split())

events = []
for j in range(q):
    _ni, l, r = map(int, input().split())
    events.append((l, "l", j))
    events.append((r + 0.5, "r", j))
events.sort(reverse=True)
cnt = n
keys = k
ans = ["0"] * q
for _, d, j in events:
    if d == "l":
        cnt += 1
        if ans[j] == "1":
            keys += 1
        continue

    cnt -= 1

    if cnt == 0:
        if keys == 0:
            print("impossible")
            exit(0)
        keys -= 1
        ans[j] = "1"

# print(ans)
print("".join(ans))
