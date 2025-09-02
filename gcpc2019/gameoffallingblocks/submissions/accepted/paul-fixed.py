import sys
positions = {'I':(1,1), 'J':(2,2), 'L':(2,2), 'O':(0,5), 'S':(1,7), 'T':(1,9), 'Z':(1,7)}

while True:
    c = raw_input()
    if c == 'W': break
    print('%d %d\n' % positions[c])
    sys.stdout.flush()
