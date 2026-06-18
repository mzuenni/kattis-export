from collections import defaultdict

n = int(input())
by_item = defaultdict(list)
for _ in range(n):
    k,v = input().split()
    by_item[v].append(k=="pickup")

if all(x == [True,False] for x in by_item.values()):
    print("yes")
else:
    print("no")
