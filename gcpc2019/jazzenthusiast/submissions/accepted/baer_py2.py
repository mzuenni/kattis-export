import time
n, c = map(int, raw_input().split(" "))
ps = [raw_input().split(":") for _ in range(n)]
x = sum(int(p[0]) * 60 + int(p[1]) for p in ps) - c * (n-1)
print("%02d:%02d:%02d" % (x / 3600, x / 60 % 60, x % 60))
