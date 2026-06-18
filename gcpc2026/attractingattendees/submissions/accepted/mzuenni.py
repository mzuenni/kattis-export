bands, fans, lim = map(int, input().split())
adj = [[] for _ in range(bands + fans)]
for i in range(fans):
	k = int(input())
	bs = [int(x) - 1 for x in input().split()]
	adj[i + bands] = bs
	for b in bs:
		adj[b].append(i + bands)

deg = [len(x) for x in adj]

def remove(i):
	if deg[i] <= 0:
		return False
	if i < bands:
		return deg[i] < lim
	else:
		return 2*deg[i] < len(adj[i])


todo = [i for i in range(bands + fans) if remove(i)]
for x in todo:
	deg[x] = 0;

while todo:
	c = todo.pop()
	for x in adj[c]:
		deg[x] -= 1
		if remove(x):
			todo.append(x)
			deg[x] = 0

res = [i+1 for i in range(bands) if deg[i] > 0]
if res:
	print("possible")
	print(len(res))
	print(*res)
else:
	print("impossible")
