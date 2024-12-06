#!/usr/bin/env python3

(n, k), s = map(int, input().split()), input()

f_i_1 = [2 * x % n for x in range(n)]


def f_i_pow_k(k):
    if k == 0:
        return list(range(n))
    if k == 1:
        return f_i_1
    half_f_i = f_i_pow_k(k // 2)
    new_f_i = [half_f_i[half_f_i[x]] for x in range(n)]
    return [new_f_i[f_i_1[x]] for x in range(n)] if k & 1 else new_f_i


f_i_k = f_i_pow_k(k)
print("".join(s[f_i_k[i]] for i in range(n)))
