#checks whether 
#   1. there are really at most n=10000 different names
#   2. no self edges

max_n=10000

m=int(input())

names=set()
for _ in range(m):
    first, sep, second = input().split()
    if first == second:
        exit(43)#self_edge!
    names.add(first)
    names.add(second)
    
if len(names) > max_n:
    exit(43)#too many names

exit(42)#everything OK

