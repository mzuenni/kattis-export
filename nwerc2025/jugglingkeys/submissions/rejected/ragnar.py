#!/usr/bin/env python3
# @EXPECTED_RESULTS@: RUN_TIME_ERROR, WRONG_ANSWER
n, k, q = map(int, input().split())

events = []
for j in range(q):
    n, l, r = map(int, input().split())
    events.append((l, n-1, 'l', j))
    events.append((r + 0.5, n-1, 'r', j))
events.sort(reverse=True)
cnt = n
ans = []
keys = k
person_keys = [0] * n
ans = ['0'] * q
for _, i, d, j in events:
    if d == 'l':
        cnt += 1
        if person_keys[i]:
            keys += 1
            person_keys[i] = False
        # print('left', i, 'cnt', cnt, 'keys', keys)
        continue

    cnt -= 1

    if cnt == 0:
        if keys == 0:
            print('impossible')
            exit(0)
        keys -=1
        ans[j] = '1'
        person_keys[i] = True
    # print('left', i, 'cnt', cnt, 'keys', keys)

# print(ans)
print(''.join(ans))
