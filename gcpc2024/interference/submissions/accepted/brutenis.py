n, w = map(int, input().split())

waves = []
for i in range(n):
    c, *xs = input().split()
    if c == "!":
        waves.append([int(a) for a in xs])
    else:
        query = int(xs[0])
        answer = 0
        for pos, length, amplitude in waves:
            if pos <= query < pos+length:
                answer += [amplitude, 0, -amplitude, 0][(query - pos)%4]
        print(answer)


