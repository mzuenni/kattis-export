import sys, random

random.seed(int(sys.argv[1]))
n = int(sys.argv[2])
m = int(sys.argv[3])

edges = []
for i in range(n-1):
    edges.append([i, i+1])

perm = list(range(1, n+1))
random.shuffle(perm)

for i in range(len(edges)):
    edges[i][0] = perm[edges[i][0]]
    edges[i][1] = perm[edges[i][1]]
    if random.randint(0, 1):
        edges[i][0], edges[i][1] = edges[i][1], edges[i][0]

random.shuffle(edges)

root = perm[0]

print(n)
for e in edges:
    print(e[0], e[1], random.randint(1, 10**6))

bridges = []
s = set()

suf = [0] * n
for i in range(m - n):
    u = -1
    v = -1
    while (u, v) in s or abs(u-v) <= 1:
        u = random.randint(1, n-1)
        v = random.randint(1, n-1)

    bridges.append([perm[u], perm[v]])
    s.add((u, v))
    s.add((v, u))
    suf[max(u, v)] ^= 1
    suf[min(u, v)] ^= 1

for i in range(n-1, 1, -1):
    if suf[i] == 0:
        suf[i] ^= 1
        bridges.append([perm[0], perm[i]])
        if random.randint(0, 1):
            bridges[-1][0], bridges[-1][1] = bridges[-1][1], bridges[-1][0]


random.shuffle(bridges)

print(len(bridges))
for e in bridges:
    print(*e)
