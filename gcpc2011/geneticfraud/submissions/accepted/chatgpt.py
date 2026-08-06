import sys

def longest_similar_region(a, b):
    n = len(a)
    dp = [0] * (n + 1)
    best = 0

    for i in range(1, n + 1):
        prev = 0
        ai = ord(a[i - 1])
        for j in range(1, n + 1):
            tmp = dp[j]
            if abs(ai - ord(b[j - 1])) <= 1:
                v = prev + 1
                dp[j] = v
                if v > best:
                    best = v
            else:
                dp[j] = 0
            prev = tmp

    return best

def solve():
    data = sys.stdin.read().split()
    t = int(data[0])
    idx = 1
    out = []
    for _ in range(t):
        n = int(data[idx]); idx += 1
        s1 = data[idx]; idx += 1
        s2 = data[idx]; idx += 1
        longest = longest_similar_region(s1, s2)
        out.append("POSITIVE" if longest * 2 >= n else "NEGATIVE")
    sys.stdout.write("\n".join(out))

solve()
