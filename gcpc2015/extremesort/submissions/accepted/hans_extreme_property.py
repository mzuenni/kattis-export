
import builtins
import itertools

N = int(eval(input()))
A = [int(x) for x in input().split(' ')]

# extremely literal
# extremely pointless
indices = itertools.product(list(range(N)), list(range(N)))
X = [A[j] - A[i] if i < j else 9001 for i, j in indices]
extreme_property = min(X) >= 0

print("yes" if extreme_property else "no")
