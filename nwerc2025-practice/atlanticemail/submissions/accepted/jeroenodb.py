operation = input()
if operation == "send":
    n = int(input())
    s = input()
    tosend = [[1]*5 for i in range(5)]
    for i in range(5):
        tosend[i][i]=0
    for ch in s:
        for j in range(5):
            bit = (ord(ch)-ord('a'))>>j&1
            tosend[j].append(bit)
    for bitstring in tosend:
        print(''.join(str(i) for i in bitstring))
else:
    assert(operation=="receive")
    channels = [input() for i in range(5)]
    channels.sort()
    channels = [bs[5:] for bs in channels]
    n = len(channels[0])
    email = [0]*n

    for i in range(n):
        cur = 0
        for j in range(5):
            email[i]+=int(channels[j][i])<<j

    print(''.join(chr(c+ord('a')) for c in email))


