#usage: python3 visualizer.py < data/<dir>/<TC>.in
# shows the 1000^2 coordinates around the origin

from PIL import Image

img = Image.new('RGB', (1000, 1000), color='white')

n = int(input())
for i in range(n):
    x, y, w, h = map(int, input().split())
    for j in range(w):
        xx = x+j+500;
        if xx < 0 or xx >= 1000:
            continue
        for k in range(h):
            yy = y+k+500
            if yy < 0 or yy >= 1000:
                continue
            img.putpixel((xx,999-yy),(0,0,0))

img.show()
