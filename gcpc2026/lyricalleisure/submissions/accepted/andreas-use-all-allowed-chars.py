n, k = map(int, input().split())
print(('a' * (k-1) + 'A' + 'bcdefghijklmnopqrstuvwxyzBCDEFGHIJKLMNOPQRSTUVWXYZ' * n)[:n])
