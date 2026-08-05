import sys

input = sys.stdin.readline

C, N, O = map(int, input().split())

size = 1
while size < C:
    size <<= 1

mn = [0] * (2 * size)
mx = [0] * (2 * size)
lazy = [0] * (2 * size)


def apply(x, v):
    mn[x] += v
    mx[x] += v
    lazy[x] += v


def push(x):
    if lazy[x]:
        apply(x * 2, lazy[x])
        apply(x * 2 + 1, lazy[x])
        lazy[x] = 0


def pull(x):
    mn[x] = min(mn[x * 2], mn[x * 2 + 1])
    mx[x] = max(mx[x * 2], mx[x * 2 + 1])


def range_add(x, lx, rx, l, r, v):
    if l <= lx and rx <= r:
        apply(x, v)
        return
    push(x)
    mid = (lx + rx) // 2
    if l < mid:
        range_add(x * 2, lx, mid, l, r, v)
    if r > mid:
        range_add(x * 2 + 1, mid, rx, l, r, v)
    pull(x)


def range_min(x, lx, rx, l, r):
    if l <= lx and rx <= r:
        return mn[x]
    push(x)
    mid = (lx + rx) // 2
    res = 10 ** 18
    if l < mid:
        res = min(res, range_min(x * 2, lx, mid, l, r))
    if r > mid:
        res = min(res, range_min(x * 2 + 1, mid, rx, l, r))
    return res


def range_max(x, lx, rx, l, r):
    if l <= lx and rx <= r:
        return mx[x]
    push(x)
    mid = (lx + rx) // 2
    res = -10 ** 18
    if l < mid:
        res = max(res, range_max(x * 2, lx, mid, l, r))
    if r > mid:
        res = max(res, range_max(x * 2 + 1, mid, rx, l, r))
    return res


def point_query(x):
    return range_min(1, 0, size, x, x + 1)


for _ in range(O):
    cmd = input().split()

    if cmd[0] == "state":
        x = int(cmd[1])
        print(point_query(x))

    elif cmd[0] == "change":
        x = int(cmd[1])
        S = int(cmd[2])

        cur = point_query(x)

        if S > 0:
            d = min(S, N - cur)
        else:
            d = -min(-S, cur)

        if d:
            range_add(1, 0, size, x, x + 1, d)

        print(d)

    else:  # groupchange
        A = int(cmd[1])
        B = int(cmd[2])
        S = int(cmd[3])

        if S > 0:
            limit = range_max(1, 0, size, A, B + 1)
            d = min(S, N - limit)
        else:
            limit = range_min(1, 0, size, A, B + 1)
            d = -min(-S, limit)

        if d:
            range_add(1, 0, size, A, B + 1, d)

        print(d)
