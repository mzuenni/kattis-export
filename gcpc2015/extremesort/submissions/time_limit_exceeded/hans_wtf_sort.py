
def wtf_sort(arr):
    result = arr[:]
    end = len(result)
    happy = 0
    while happy < end:
        wtf = 0
        for i in range(end):
            if result[i] < result[happy]:
                wtf = i

        if wtf > happy:
            for i in range(happy, end-1):
                result[i], result[i+1] = result[i+1], result[i]
        else:
            happy += 1
    return result


N = int(eval(input()))
data = [int(x) for x in input().split(' ')]

print("yes" if data == wtf_sort(data) else "no")
