'''
Created on 18.05.2017

@author: Moritz Fuchs
'''

n = int(raw_input())
max_x = 0
min_x = 100000000
max_y = 0
min_y = 100000000
l = list()
for _ in range(n):
    x,y,c = map(int, raw_input().split())
    max_x = max(max_x,x)
    min_x = min(min_x,x)
    max_y = max(max_y,y)
    min_y = min(min_y,y)
    l.append((x,y,c))
l.sort()

upper_tube_y = min_y - 5.0 
upper_base_y = min_y-1.0
lower_base_y = max_y+1.0

res_inner = list()
res_outer = list()
s = l[0]
outer_x = (l[0][0] - 0.3)
outer_y = upper_tube_y
inner_x = (l[0][0] + 0.3)
inner_y = upper_tube_y + 0.5

res_inner.append((inner_x, inner_y))
res_outer.append((outer_x, outer_y))

current_x = l[0][0]
for p in l:
    if p[0] != current_x:
        # Bring tube to next column
        
        #step 1: bring tube to bottom
        res_inner.append((current_x+0.2, lower_base_y-0.5))
        res_outer.append((current_x-0.2, lower_base_y))
        
        #step 2: bring tube between current and next column
        res_inner.append((current_x+0.3, lower_base_y-0.5))
        res_outer.append((current_x+0.4, lower_base_y))
        
        #step 3: move back to the top
        res_inner.append((current_x+0.3, upper_base_y))
        res_outer.append((current_x+0.4, upper_base_y+0.5))
        
        #step 4: bring tube to next column
        res_inner.append((p[0]+0.2, upper_base_y))
        res_outer.append((p[0]-0.3, upper_base_y+0.5))
        
        current_x = p[0]
        
    if p[2] == 1:
        # put color 0 on the inside
        res_inner.append((p[0]-0.1, p[1]))
        res_outer.append((p[0]-0.2, p[1]))
    elif p[2] == 2:
        # put color 1 inside the tube
        res_inner.append((p[0]+0.1, p[1]))
        res_outer.append((p[0]-0.1, p[1]))
    else:
        # put color 2 outside
        res_inner.append((p[0]+0.2, p[1]))
        res_outer.append((p[0]+0.1, p[1]))

#connect tube to start
        
#step 1: bring tube to bottom
res_inner.append((current_x+0.2, lower_base_y-0.5))
res_outer.append((current_x-0.2, lower_base_y))

#step 2: bring tube between current and next column
res_inner.append((current_x+0.5, lower_base_y-0.5))
res_outer.append((current_x+0.6, lower_base_y))

#step 3: move back to the top
res_inner.append((current_x+0.5, upper_tube_y+0.5))
res_outer.append((current_x+0.6, upper_tube_y))


print(len(res_outer))
for x in res_outer:
    print("%.1f %.1f"%x)
print(len(res_inner))
for x in res_inner:
    print("%.1f %.1f"%x)     
    