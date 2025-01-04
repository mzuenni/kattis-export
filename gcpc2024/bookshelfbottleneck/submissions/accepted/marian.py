n, h = map(int, input().split())
w = 0
for _ in range(n):
    dims = list(map(int, input().split()))
    dims.sort(reverse=True)
    for d in dims:
        if d <= h:
            dims.remove(d)
            break
    if len(dims) == 3:
        print("impossible")
        exit(0)
    w += dims[-1]
print(w)
