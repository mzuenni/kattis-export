
import builtins
from collections import defaultdict
import re

N = int(eval(input()))
adj = defaultdict(list)
entry = []
visited = {}

for i in range(N):
    method, _ = input().split(' ')
    callers = input().split(' ')
    if callers == ['']:
        callers = []

    visited[method] = False
    if re.search('::PROGRAM$', method):
        entry.append(method)

    for caller in callers:
        adj[caller].append(method)

todo = entry[:]
while len(todo) > 0:
    cur = todo.pop(0)
    visited[cur] = True
    for to in adj[cur]:
        if not visited[to]:
            visited[to] = True
            todo.append(to)

print(sum([1 for vis in list(visited.values()) if not vis]))
