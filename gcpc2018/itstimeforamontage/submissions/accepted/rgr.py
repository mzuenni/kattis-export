n = int(input())
h = list(map(int, input().split()))
v = list(map(int, input().split()))

diff = v[0] - h[0]

if diff < 0:
    print(0)

else:
    for i in range(n):
        if h[i]+diff < v[i]:
            print(diff+1)
            break
        elif h[i]+diff > v[i]:
            print(diff)
            break
    else:
        print(diff)
