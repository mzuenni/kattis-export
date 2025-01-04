#!/bin/python3

# n humans & m friendships.
n, m = map(int, input().split())


# Union-Find data structure
class UnionFind:
    def __init__(self, size):
        self.parent = [i for i in range(size)]
        self.size = [1] * size

    def find(self, x):
        if x != self.parent[x]:
            self.parent[x] = self.find(self.parent[x])  # Path compression
        return self.parent[x]

    def union(self, x, y):
        rootX = self.find(x)
        rootY = self.find(y)

        if rootX != rootY:
            if self.size[rootX] < self.size[rootY]:  # Union by size
                rootX, rootY = rootY, rootX

            self.parent[rootY] = rootX
            self.size[rootX] += self.size[rootY]


uf = UnionFind(n)

# Read friendships.
for _ in range(m):
    a, b = map(int, input().split())
    a -= 1
    b -= 1

    # Merge components of a and b, if they are friends. This way, we can
    # determine the size of the component containing a or b by looking at uf.size.
    uf.union(a, b)


# The solution is the maximum component size.
print(max(uf.size))
