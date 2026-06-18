import sys

n = int(sys.argv[1])
rev = bool(int(sys.argv[2]))

a = [*range(1, n+1)]
if rev:
    a = a[::-1]

print(n)
print(*a)
