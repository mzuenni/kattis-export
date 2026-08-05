# this is a translation of EgorDP.java to python
#
# this solution imitates/is inspired by the usual dp solution (the whole calculation is modulo g[0])
# 
# However, because we have not n but endless many items it is not so easy: we must calculate what happens
# if we add 1,2,3, and so on objects of the type i.
# 
# So for N items types and g[0]=M we get O(N*M*M) running time.
#

MAX_VAL=float("inf")

def getMinDists(gs, MAX):
  n=len(gs)
  dists=[MAX_VAL]*MAX
  dists[0]=0;
  for g in gs:
     for j in range(MAX):
       if dists[j]!=MAX_VAL:
        current=j
        while True:
          next=(current+g)%MAX;
          nextValue=dists[current]+g
          if dists[next]<=nextValue:
            break
          dists[next]=nextValue
          current=next
  return dists

N,K=list(map(int, input().split()))
gs=list(map(int, input().split()))

MAX=gs[0]
gs=gs[1:]

minDists=getMinDists(gs, MAX)
index=K%MAX

print("possible" if minDists[index]<=K else "impossible")     

