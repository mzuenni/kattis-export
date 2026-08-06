MAXTESTCASES = 20
MAXCITIES = 1000000000
MAXRANGES = 100000

print MAXTESTCASES

for n in range(MAXTESTCASES):
    nc = MAXCITIES - n
    nr = MAXRANGES - n
    if n % 2 == 0:
        rangelen = n
    else:
        rangelen = nc - n
    print nc, nr
    for x in range(nr):
        print x, (x + rangelen) % nc
