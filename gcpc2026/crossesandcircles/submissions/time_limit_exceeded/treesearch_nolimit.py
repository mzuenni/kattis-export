import functools
def has_line(cells):
    return any(z + d in cells and z - d in cells for z in cells for d in [1, 1 + 1j, 1j, -1 + 1j])
@functools.cache
def f(moves):
    team = len(moves) % 2
    if not has_line(moves[::-2]) and (team == 1 or len(moves) < 16):
        for x in range(1, 6):
            for y in range(1, 6):
                if (z := x + y * 1j) in moves:
                    continue
                if f(moves + (z, ))[0] == team:
                    return team, z
    return 1 - team, 0

a = ()
while not a or a[-1]:
    res, nx = f(a)
    assert res == 0
    print(*map(int,[nx.real, nx.imag]))
    a += (nx, complex(*map(int, input().split())))
