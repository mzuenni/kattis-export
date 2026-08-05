import sys

def is_prime(n):
    i = 2
    while i*i <= n:
        if n % i == 0:
            return False
        i += 1
    return True

line = sys.stdin.readline().rstrip()
revline = line[::-1]

if is_prime(int(line)):
    print("yes")
else:
    print("no")
