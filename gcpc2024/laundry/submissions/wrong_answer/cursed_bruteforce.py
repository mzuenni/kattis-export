import math
from functools import partial


for _ in range(int(input())):
    k = int(input())

    def brute_outer(nums, depth=3):
        a, b, c, ab, bc, ac, abc = nums
        fits_a = (k - a % k)
        fits_b = (k - b % k)
        fits_c = (k - c % k)
        fits_a = 0 if fits_a == k else fits_a
        fits_b = 0 if fits_b == k else fits_b
        fits_c = 0 if fits_c == k else fits_c
        fits_a_ab = fits_a if fits_a <= ab else 0
        fits_a_ac = fits_a if fits_a <= ac else 0
        fits_b_bc = fits_b if fits_b <= bc else 0
        fits_b_ab = fits_b if fits_b <= ab else 0
        fits_c_bc = fits_c if fits_c <= bc else 0
        fits_c_ac = fits_c if fits_c <= ac else 0

        func = partial(brute_outer, depth=depth-1) if depth > 0 else brute
        return min(
            func([a + fits_a_ab, b, c, ab - fits_a_ab, bc, ac, abc]),
            func([a + fits_a_ac, b, c, ab, bc, ac - fits_a_ac, abc]),

            func([a, b + fits_b_bc, c, ab - fits_b_bc, bc, ac, abc]),
            func([a, b + fits_b_ab, c, ab, bc - fits_b_ab, ac, abc]),

            func([a, b, c + fits_c_bc, ab, bc - fits_c_bc, ac, abc]),
            func([a, b, c + fits_c_ac, ab, bc, ac - fits_c_ac, abc]),

            func([a, b, c, ab, bc, ac, abc]),
        )

    def brute(nums):
        a, b, c, ab, bc, ac, abc = nums
        results = [
            get_loads([a+ab+ac, b+bc, c], abc),
            get_loads([a+ab+ac, b, c+bc], abc),

            get_loads([a, b+bc+ab, c+ac], abc),
            get_loads([a+ac, b+bc+ab, c], abc),

            get_loads([a, b+ab, c+ac+bc], abc),
            get_loads([a+ab, b, c+ac+bc], abc),

            get_loads([a+ab, b+bc, c+ac], abc),
            get_loads([a+ac, b+ab, c+bc], abc),
        ]

        return min(results)

    def get_loads(nums, abc):
        diff = (k - sum(nums) % k)
        diff = 0 if diff == k else diff
        abc -= diff
        abc = max(0, abc)
        return sum(num // k + bool(num % k) for num in nums) + (abc // k) + bool(abc%k)

    nums = [int(a) for a in input().split()]
    s = 0

    print(brute_outer(nums) + s)

