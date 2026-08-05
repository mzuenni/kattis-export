import sys

MOD = 10**9 + 7
idx = [-1] * 256

for i in range(26):
    idx[97 + i] = i
    idx[65 + i] = 26 + i

for i in range(10):
    idx[48 + i] = 52 + i

def solve():
    data = sys.stdin.buffer.read().split()
    t = int(data[0])
    at = 1
    ans = []

    for _ in range(t):
        k = int(data[at])
        s = data[at + 1]
        at += 2
        n = len(s)

        value = [1] * k
        count = [1] * k
        freq = [0] * (n + 2)
        total = [0] * (n + 2)

        freq[1] = k
        total[1] = k
        dp = 1
        ways = k

        for ch in reversed(s):
            c = idx[ch]
            old = value[c]

            freq[old] -= 1
            total[old] = (total[old] - count[c]) % MOD

            new = dp + 1
            value[c] = new
            count[c] = ways

            freq[new] += 1
            total[new] = (total[new] + ways) % MOD

            while freq[dp] == 0:
                dp += 1

            ways = total[dp]

        ans.append(f"{dp} {ways}")

    sys.stdout.write("\n".join(ans))

solve()