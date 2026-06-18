from collections import defaultdict

n = int(input())
item_cnt = defaultdict(int)
for _ in range(n):
    _, name = input().split()
    item_cnt[name] += 1

if all(x == 2 for x in item_cnt.values()):
    print("yes")
else:
    print("no")
