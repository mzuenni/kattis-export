N = int(input())
numbers = [int(x) for x in input().split(' ')]

if numbers == list(range(1, N+1)):
    print("yes")
else:
    print("no")
