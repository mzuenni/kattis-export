n = int(input())
nums = [int(a) for a in input().split()]

def score(pitch_change):
    return sum(abs(pitch_change + i - a) for i, a in enumerate(nums))

def ternary(lo, hi):
    if abs(lo-hi) <= 0.1:
        print(score(int(round(lo))))
        # Show final tuning
        # print(*[round(lo+i) for i in range(n)])
        return
    mid1 = lo * (2/3) + hi * (1/3)
    mid2 = lo * (1/3) + hi * (2/3)
    score1 = score(mid1)
    score2 = score(mid2)
    if score1 > score2:
        ternary(mid1, hi)
    else:
        ternary(lo, mid2)

ternary(-300_000.0, 200_000.0)
