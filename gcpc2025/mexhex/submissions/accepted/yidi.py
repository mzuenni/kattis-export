n, d = map(int, input().split())
a = [*map(int, input().split())]
b = [[]for i in range(n+1)]
for i in range(n):
    b[a[i]].append(i)

for x in range(n+1):
    last = 0
    ok = True
    i = 0
    while i < len(b[x]):
        pos = b[x][i]
        while i+1 < len(b[x]) and b[x][i+1] - b[x][i] < d:
            i += 1
        
        last = max(last, b[x][i] - d + 1)
        if last > pos:
            ok = False
        last += 2*d
        i += 1
        
    if ok:
        print(x)
        break
