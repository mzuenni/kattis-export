print(1)
print(199_999)

x = 199_996

L = x // 2 + 2

print(0, 0, 0, L)
print(0, 0, L, 0)
print(L, 0, L, L)
for i in range(x // 2):
    print(0, 2 + i, 1, 2 + i)
    print(L-1, 2 + i, L, 2+i)
