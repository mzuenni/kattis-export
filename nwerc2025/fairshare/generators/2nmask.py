import sys
mask = int(sys.argv[1])
assert 0<=mask<16
mask = f"{mask:04b}" # get 4 bit binary string

print(2)
print(int(mask[3])+1, int(mask[2])+1)
print(int(mask[1])+1, int(mask[0])+1)
