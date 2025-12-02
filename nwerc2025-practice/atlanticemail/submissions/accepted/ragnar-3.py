x = input()
if x == "send":
    n = int(input())
    s = input()
    message = ""
    for c in s:
        message += format(ord(c) - ord("a"), "05b")

    start = 0
    for i in range(5):
        end = min(start + n, len(message))

        print(
            "0" * (5 - i) + "1" * i,
            message[start:end],
            sep="",
        )
        start += n
else:
    ss = sorted([input() for _ in range(5)])
    ss = [s[5:] for s in ss]
    message = "".join(ss)
    n = len(message) // 5
    for x in range(0, len(message), 5):
        c = 0
        for j in range(5):
            c *= 2
            c += int(message[x + j])
        # print(message[x : x + 5], c)
        print(chr(c + ord("a")), end="")
