

def stooge_sort(arr, a, z):
    if arr[a] > arr[z-1]:
        arr[a], arr[z-1] = arr[z-1], arr[a]
    if z - a > 2:
        t = (z - a) // 3
        stooge_sort(arr, a, z-t)
        stooge_sort(arr, a+t, z)
        stooge_sort(arr, a, z-t)


N = int(eval(input()))
data = [int(x) for x in input().split(' ')]
verify = data[:]
stooge_sort(verify, 0, len(verify))

print("yes" if data == verify else "no")
