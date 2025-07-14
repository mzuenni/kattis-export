# @EXPECTED_RESULTS@: WRONG_ANSWER, RUN_TIME_ERROR
#!/usr/bin/env python3
import itertools

p = input()
n = int(input())
s = input()

k = min(n, 5)
a = [''.join(s) for s in itertools.product('01', repeat=k)]
b = [''.join(s) for s in itertools.product('012', repeat=k)]
b = [s for s in b if s == min(s[i:] + s[:i] for i in range(k))]

if p == 'Decode':
  a, b = b, a
  if '2' in s:
    i = s.index('2')
    s = s[i:] + s[:i]

print(b[a.index(s[:k])] + s[k:])
