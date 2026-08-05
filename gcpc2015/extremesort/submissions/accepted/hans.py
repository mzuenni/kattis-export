input()
numbers = [int(x) for x in input().split(' ')]

if numbers == sorted(numbers):
    print("yes")
else:
    print("no")
