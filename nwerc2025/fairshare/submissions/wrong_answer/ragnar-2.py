n = int(input())
ab = [tuple(map(int, input().split())) for _ in range(n)]
a = sum(x[0] for x in ab)
b = sum(x[1] for x in ab)
if a >= b:
    print(1)
else:
    print("impossible")
