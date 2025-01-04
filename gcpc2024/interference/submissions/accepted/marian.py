n, w = map(int, input().split())
waves = []
for i in range(n):
    op, *nums = input().split()
    nums = list(map(int, nums))
    if op == '!':
        waves.append(nums)
    else:
        position = nums[0]
        height = 0
        for (p, l, a) in waves:
            if p <= position < p+l:
                if (position - p) % 4 == 0:
                    height += a
                elif (position - p) % 4 == 2:
                    height -= a
        print(height)

"""
4 10
! 2 7 1
? 9
? 7
? 6
"""
