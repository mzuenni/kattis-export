from collections import defaultdict
import sys
sys.setrecursionlimit(1<<20)
n, m = map(int, input().split())

friends = defaultdict(list)

for _ in range(m):
    a, b = map(int, input().split())
    friends[a].append(b)
    friends[b].append(a)

abducted = set()

def traverse(curr):
    if curr in abducted:
        return 0
    abducted.add(curr)
    return sum([traverse(friend) for friend in friends[curr]]) + 1

largest = 1

for friend in friends:
    largest = max(largest, traverse(friend))
print(largest)
