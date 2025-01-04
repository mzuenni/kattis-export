n, h = map(int, input().split())
s = 0
for _ in range(n):
    nums = sorted(map(int, input().split()))
    if fits := [a for a in nums if a <= h]:
        fit = max(fits)
        nums.remove(fit)
        s += min(nums)
    else:
        print('impossible')
        exit(0)
print(s)
