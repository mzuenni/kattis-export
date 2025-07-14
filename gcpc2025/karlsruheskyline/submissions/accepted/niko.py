import sys
n, a, b = map(int, input().split())

if a + b > n + 1:
    print("no")
    sys.exit(0)
if a == 1 and b == 1:
    print("no")
    sys.exit(0)

swap = False
if b == 1:
    swap = True
    a, b = b, a

print("yes")
x = [0 for i in range(1, n+1)]
for i in range(a - 1):
    x[i] = i + 1
x[a - 1] = n
for i in range(b - 1):
    x[-(i + 1)] = n - b + i + 1
for i in range(a, n - b + 1):
    x[i] = i

if swap:
    x = list(reversed(x))
print(*x)
