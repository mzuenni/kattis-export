import sys

input = sys.stdin.readline

T = int(input())

for _ in range(T):
    arr = list(map(int, input().split()))
    n = arr[0]
    a = arr[1:]

    total = 0

    max_end = max_sum = a[0]
    min_end = min_sum = a[0]
    total = a[0]

    for x in a[1:]:
        total += x

        max_end = max(x, max_end + x)
        max_sum = max(max_sum, max_end)

        min_end = min(x, min_end + x)
        min_sum = min(min_sum, min_end)

    circular = total - min_sum
    print(max(0, max(max_sum, circular)))
