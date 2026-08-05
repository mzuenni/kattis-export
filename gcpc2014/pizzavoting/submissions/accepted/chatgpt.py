import sys

a = sys.stdin.buffer.read().split()
n, p = map(int, a[:2])

q, r = divmod(n - 1, 3)

need_high = q + (r > 0)
need_low = q + (r == 2)

print("YES" if n - p >= need_high and p - 1 >= need_low else "NO")
