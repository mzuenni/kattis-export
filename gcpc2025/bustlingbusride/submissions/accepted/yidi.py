n, b, delay, w = map(int, input().split())
a = [*map(int, input().split())]
for i in range(1, b):
    a[i] += a[i-1]
c = [*map(int, input().split())]
for i in range(n):
    c[i] -= 1

def upd(seg, i, x):
    i += b
    seg[i] += x
    while i > 1:
        i //= 2
        seg[i] = seg[2*i] + seg[2*i+1]

def query(seg, l, r):
    ans = 0
    l += b
    r += b
    while l < r:
        if l&1:
            ans += seg[l]
            l += 1
        if r&1:
            r -= 1
            ans += seg[r]
        
        l //= 2
        r //= 2

    return ans

seg1 = [0] * (2*b)
seg2 = [0] * (2*b)
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
        while ptr < n:
            mx = max(mx, a[c[ptr]])
            t += query(seg1, 0, c[ptr]) * w * 2
            if not used[c[ptr]]:
                t += query(seg2, c[ptr]+1, b) * w * 2
                upd(seg1, c[ptr], 1)
                used[c[ptr]] = 1
            upd(seg2, c[ptr], 1)
            t += 2*w
            if t + mx > mid:
                break

            ptr += 1

        while rem < n and rem <= ptr:
            if used[c[rem]]:
                upd(seg1, c[rem], -1)
            used[c[rem]] = 0
            upd(seg2, c[rem], -1)
            rem += 1

    if ptr < n:
        l = mid
    else:
        r = mid

print(r)
