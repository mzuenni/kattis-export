from string import ascii_lowercase as lower

n = int(input())
names = [input() for _ in range(n)]
names.sort(key=lambda s: s.lstrip(lower+" '"))
print(*names, sep='\n')
