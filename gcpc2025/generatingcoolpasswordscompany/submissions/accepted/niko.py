import random

n = int(input())

for i in range(n):
    print("aA0+", end='')
    for x in range(4,12):
        print(chr(random.randrange(33,126)), end='')
    print()
