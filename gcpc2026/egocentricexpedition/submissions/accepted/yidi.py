T = int(input())
for t in range(T):
    print("? 0 1", flush=True)
    d1 = float(input())
    print("? 1 1", flush=True)
    d2 = float(input()) * 0.5**0.5

    d = abs(d1*d2 / (d2**2 + (d1-d2)**2)**0.5)
    A = d*d*4
    assert(abs(round(A) - A) < 1e-7)
    print("!", int(round(A)), flush=True)
