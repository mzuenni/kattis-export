n, b, delay, w = map(int, input().split())
a = [*map(int, input().split())]
for i in range(1, b):
    a[i] += a[i-1]
c = [*map(int, input().split())]
for i in range(n):
    c[i] -= 1

def upd(seg, i, x):
    i += 1
    while i < b:
        seg[i] += x
        i += i & (-i)

sm = 0
def query(seg, r):
    if r == b:
        return sm
    ans = 0
    while r > 0:
        ans += seg[r]
        r -= r & (-r)
    return ans

seg1 = [0] * (b+1)
seg2 = [0] * (b+1)
used = [0] * b

l = 0
r = 2 * 10 ** 18
while l+1 < r:
    mid = (l+r) // 2
    ptr = 0
    bus = 0
    while ptr < n:
        t = bus * delay
        bus += 1
        if t + 2*w + c[ptr] > mid:
            break

        mx = 0
        rem = ptr
        sm = 0
        while ptr < n:
            mx = max(mx, a[c[ptr]])
            t += query(seg1, c[ptr]) * w * 2
            if not used[c[ptr]]:
                t += (sm - query(seg2, c[ptr]+1)) * w * 2
                upd(seg1, c[ptr], 1)
                used[c[ptr]] = 1
            upd(seg2, c[ptr], 1)
            sm += 1
            t += 2*w
            if t + mx > mid:
                break

            ptr += 1

        while rem < n and rem <= ptr:
            if used[c[rem]]:
                upd(seg1, c[rem], -1)
            used[c[rem]] = 0
            upd(seg2, c[rem], -1)
            sm -= 1
            rem += 1

    if ptr < n:
        l = mid
    else:
        r = mid

print(r)
