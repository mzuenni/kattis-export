n = int(input())
nums = [int(a) for a in input().split()]

def score(pitch_change):
    return sum(abs(pitch_change + i - a) for i, a in enumerate(nums))

# using three intervals is not needed for integers
def ternary(lo, hi):
    while hi - lo > 1:
        mid = (hi + lo) // 2
        if score(mid) < score(mid + 1):
            hi = mid
        else:
            lo = mid

    print(score(lo + 1))
ternary(-300_000, 200_000)
