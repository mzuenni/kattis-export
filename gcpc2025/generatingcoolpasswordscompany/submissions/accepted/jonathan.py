from random import shuffle, choice, seed, randrange
seed(34689358)
from string import ascii_lowercase, ascii_uppercase
digits = "".join(map(str, range(10)))
special = "!\"#$%&'()*+,-./:;<=>?@[\\]^_{|}~"

n = int(input())
for _ in range(n):
    w = [choice(ascii_lowercase), choice(ascii_uppercase), choice(digits), choice(special)]
    for _ in range(randrange(4, 9)):
        w.append(choice(ascii_lowercase + ascii_uppercase + digits + special))
    shuffle(w)
    print("".join(w))
