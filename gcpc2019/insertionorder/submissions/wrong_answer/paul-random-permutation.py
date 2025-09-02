import random
n = int(raw_input().split(' ')[0])
perm = range(1,n+1)
random.shuffle(perm)
print(' '.join([str(x) for x in perm]))
