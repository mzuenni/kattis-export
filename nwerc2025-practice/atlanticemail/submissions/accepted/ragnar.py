x = input()
if x == "send":
    n = input()
    s = input()
    for i in range(5):
        print(
            "0" * (5 - i) + "1" * i,
            *(((ord(x) - ord("a")) >> i & 1) for x in s),
            sep="",
        )
else:
    ss = sorted([input() for _ in range(5)])
    ss = [s[5:] for s in ss]
    for i in range(len(ss[0])):
        c = 0
        for j in range(5):
            c |= int(ss[j][i]) << j
        print(chr(c + ord("a")), end="")
