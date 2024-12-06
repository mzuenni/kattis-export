#!/usr/bin/env python3

# n: racks
# m: books
# x: initial width
# y: new width
n, m, x, y = map(int, input().split())
# a: rack height
a = sorted(list(map(int, input().split())))
# b: book height
b = sorted(list(map(int, input().split())))

# Pack books in reduced racks from small to large
cnt = [0] * (n + 1)
for i in range(n):
    first = cnt[i]
    last = first
    while last < m and b[last] <= a[i] and last < first + y:
        last += 1
    cnt[i + 1] = last
if cnt[n] == m:
    print(n)
    exit(0)
# Pack books in original racks from large to small
cnt2 = [m] * (n + 1)
for i in range(n - 1, -1, -1):
    first = cnt2[i + 1]
    last = first
    while last > 0 and b[last - 1] <= a[i] and last > first - x:
        last -= 1
    cnt2[i] = last
    if cnt2[i] <= cnt[i]:
        print(i)
        exit(0)

print("impossible")
