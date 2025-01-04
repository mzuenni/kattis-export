line = list("bdpq")
orig = list(input().strip())

flip = False
for q in input():
    for i, l in enumerate(line):
        index = "bdpq".index(l)
        if q == "h":
           line[i] = "dbqp"[index]
        if q == "v":
           line[i] = "pqbd"[index]
        if q == "r":
           line[i] = "qpdb"[index]
    flip ^= q in "hr"

for i, c in enumerate(orig):
    orig[i] = line["bdpq".index(c)]

if flip:
    orig = orig[::-1]
print(''.join(orig))

