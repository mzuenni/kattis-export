bdpq = input()
operations = input()

mirrored = False
keys = ['b','d','p','q']
originalKeys = keys.copy()
for op in operations:
    if op == 'h':
        moves = {'b': 'd', 'd': 'b', 'p': 'q', 'q': 'p'}
        mirrored = not mirrored
    elif op == 'v':
        moves = {'b': 'p', 'p': 'b', 'd': 'q', 'q': 'd'}
    elif op == 'r':
        moves = {'b': 'q', 'q': 'b', 'p': 'd', 'd': 'p'}
        mirrored = not mirrored

    for i in range(len(keys)):
        keys[i] = moves[keys[i]]

if mirrored:
    bdpq = reversed(bdpq)

key_mapping = dict(zip(originalKeys, keys))
print(''.join(map(lambda c: key_mapping[c], bdpq)))


