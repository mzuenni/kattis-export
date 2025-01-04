#!/usr/bin/env python3
import random

n = int(input())
cards = [input() for _ in range(n)]
input()

random.seed(n + sum(hash(c) for c in cards))

me = random.randrange(2)
print('me' if me else 'you', flush=True)
for i in range(n):
  if i%2 != me:
    c = random.choice(cards)
    print(c, flush=True)
    cards.remove(c)
  else:
    cards.remove(input())
