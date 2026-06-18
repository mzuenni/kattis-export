a = [["."]*100 for i in range(100)]

x = int(input())
if x == 1:
    print("4 4 O#O# #.#. O#O# #.#.")
    exit(0)
for h in range(3, 95):
    for c in range(2, 95):
        if h * c - x in [3, 4, 6, 7, 8, 9, 10, 12, 13, 14, 15, 16]:
            for i in range(0, h+1, 2):
                a[i+2][1] = a[i+3][0] = '#'
                a[i+3][1] = 'O'
                a[h+1-i][c+2] = a[h-i][c+3] = '#'
                a[h-i][c+2] = 'O'
            for j in range(0, c+1, 2):
                a[h+2][j+2] = a[h+3][j+3] = '#'
                a[h+2][j+3] = 'O'
                a[1][c+1-j] = a[0][c-j] = '#'
                a[1][c-j] = 'O'

            x = h * c - x
            for i in range(2, 100, 2):
                if x == 0:
                    break
                if x % 4 > 0:
                    a[2][i+1] = a[3][i] = '#'
                    a[2][i] = 'O'
                    x -= 3
                else:
                    a[3][i] = a[2][i+1] = '#'
                    a[3][i+1] = 'O'
                    x -= 4
            ok = x == 0
            

            print(100, 100)
            for e in a:
                print(''.join(e))
            exit(0)
