#!/usr/bin/env python3

def slot(c):
  o, x = c.split()
  return ('+*'.index(o) * 2 + int(x) % 2) % 3

n = int(input())
cards = [set() for _ in range(3)]
for _ in range(n):
  c = input()
  cards[slot(c)].add(c)
cur = int(input()) % 2

b, c = map(len, cards[1:])
me = c <= 1 and (b if c else cur+b) % 2 == 1
even = not me
print('me' if me else 'you')

def choose_and_play(ks):
  k = next(k for k in ks if cards[k])
  print(cards[k].pop(), flush=True)

while any(cards):
  if not me:
    c = input()
    cards[slot(c)].remove(c)
  elif even:
    b, c = map(len, cards[1:])
    choose_and_play([0,1,2] if c != 1 else [2-b%2])
  else:
    choose_and_play([2,1,0])
  me = not me
