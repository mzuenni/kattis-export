import sys


def solve(n):
    num =    [500,200,100,50,20,10,5,2,1]
    atmost = [999,999,  1, 1, 4, 1,1,4,1]
    ans = []
    coins = []
    def check():
        nonlocal coins, n
        if n%2==1: return True
        dp = [0]*(n//2+1)
        dp[0]=1
        for c in coins:
            for j in range(n//2+1-c)[::-1]:
                if dp[j]: dp[j+c]=1
        return not dp[n//2]
    iters=0
    def rec(at,left):
        
        nonlocal coins,n,ans,iters
        iters+=1
        if at==len(num):
            if left==0:
                if check():
                    ans=list(i for i in coins)
                    return True
                else:
                    return False
            return False
        cur=len(coins)
        for take in range(atmost[at]+1):
            if take*num[at]>left:
                break
            if rec(at+1,left-take*num[at]): return True
            coins.append(num[at])
        while len(coins)>cur:
            coins.pop()
        return False
    if not rec(0,n):
        print(iters,file=sys.stderr)

        print("splittable")
    else:
        print(iters,file=sys.stderr)

        print(len(ans))
        print(*ans)
n = int(input())
solve(n)