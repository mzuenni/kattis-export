n = 200000
m = 5*10**8
OFF = m
print(1)
print(n)
for i in range(n//2):
    print(OFF+-i-1, OFF-m, OFF-i-1, OFF+m)

for i in range(n//2):
    print(OFF,i+OFF, m+OFF, i+OFF)