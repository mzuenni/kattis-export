import sys

def solve():
    input = sys.stdin.readline

    t = int(input())
    for _ in range(t):
        s = input().rstrip("\n")

        freq = [0] * 26
        for ch in s:
            if ch != ' ':
                freq[ord(ch) - ord('A')] += 1

        mx = max(freq)
        if freq.count(mx) != 1:
            print("NOT POSSIBLE")
            continue

        enc = freq.index(mx)
        d = (enc - (ord('E') - ord('A'))) % 26

        res = []
        for ch in s:
            if ch == ' ':
                res.append(' ')
            else:
                x = (ord(ch) - ord('A') - d) % 26
                res.append(chr(x + ord('A')))
        print(d, "".join(res))

solve()
