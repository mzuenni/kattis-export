#!/usr/bin/env python3
from sys import stdin

def main():
    n = int(stdin.readline())
    p = [int(i) for i in stdin.readline().split()]
    p.sort(reverse=True)

    total = sum(p)
    ans = 0
    dp = [0 for _ in range(total + 1)]
    dp[0] = 1
    for i in p:
        for j in range(total, i - 1, -1):
            if j > total - j and (j - i) <= total - (j - i):
                ans += dp[j - i]
            dp[j] += dp[j - i]

    print(ans)

if __name__ == "__main__":
    main()
