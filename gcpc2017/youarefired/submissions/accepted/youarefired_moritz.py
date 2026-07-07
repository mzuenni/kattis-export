n,d,k = list(map(int, input().split()))
l = list()

for i in range(n):
    x = input().split()
    l.append((int(x[1]),x[0]))

l.sort(reverse=True)
s = 0
fired = []
while l and s < d and len(fired) < k:
    f = l.pop(0)
    s += f[0]
    fired.append(f[1])

if s < d:
    print("impossible")
else:
    print(len(fired))
    for x in fired:
        print("%s, YOU ARE FIRED!"%x)
