#!/usr/bin/env python2

n = int(raw_input())
cnt = [int(i) for i in raw_input().split()]

area = 0
for i in range(n + 1):
    area += (1 << i) ** 2 * cnt[i]

i = 1;
while i * i <= area:
    if area % i != 0:
        i += 1
        continue

    current_area = 0
    possible = True
    for k in range(n, -1, -1):
        border_length = 1 << k;
        current_area += border_length ** 2 * cnt[k]
        a = (i // border_length) * border_length
        b = ((area // i) // border_length) * border_length
        if (a * b < current_area):
            possible = False
            break

    if possible:
        print i, area // i
        break

    i += 1

else:
    print("impossible")
