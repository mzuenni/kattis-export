import random
import sys
import string

random.seed(int(sys.argv[1]))
n = int(sys.argv[2])
valid = sys.argv[3] == "1"
k = 20
if len(sys.argv) > 4:
    k = int(sys.argv[4])

items = []
for i in range(n):
    if i<n//2:
        name_len = random.randint(10,k)
        item = ''.join(random.choices(string.ascii_lowercase, k=name_len))
        items.append(item)
    else:
        items.append(items[i-n//2])
random.shuffle(items)

seen = set()
print(n)
for item in items:
    if valid:
        if not item in seen:
            print("pickup", item)
            seen.add(item)
        else:
            print("dropoff", item)
    else:
        task = random.choice(['pickup', 'dropoff'])
        print(task, item)
