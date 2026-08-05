
def prime(n):
    if n == 2:
        return True
    if n < 2 or n % 2 == 0:
        return False
    for f in range(3, int(n**0.5)+1, 2):
        if n % f == 0:
            return False
    return True

def prime2(n):
    if n == 2:
        return True
    if n < 2 or n % 2 == 0 or n % 3 == 0:
        return False
    end = int(n**0.5)+1
    for f in range(5, end, 6):
        if n % f == 0 or n % (f+2) == 0:
            return False
    return True

def check(n):
    for bad in "347":
        if bad in n:
            return "no"

    u = n[::-1]
    u = u.replace("6", "9")
#    u = u.replace("9", "6")
#    u = u.replace("x", "9")
    n, u = int(n), int(u)

    if not prime(n) or not prime(u):
        return "no"
    return "yes"

print(check(input()))
