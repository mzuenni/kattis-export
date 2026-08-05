import sys

input = sys.stdin.readline

t = int(input())

for _ in range(t):
    n, a, b = map(int, input().split())

    x = a  # amount for Alice
    ans = 0

    for k in range(n, 0, -1):
        size = 1 << k
        if x == 0 or x == size:
            break
        ans += 1
        half = size >> 1
        if x > half:
            x -= half

    print(ans)
