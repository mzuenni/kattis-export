#!/usr/bin/env python3
import copy
import random

STRIP = 5

n, d = list(map(int, input().split()))
d -= 2*STRIP # now distance between the end points
n, d = list(map(int, input().split()))
vs = []
for _ in range(n):
	vs += [int(input())]
dp = []
for _ in range(n+1):
	x = []
	for _2 in range(n+1):
		line = [0] * (d + STRIP * (n+1) + STRIP)
		x += [line]
	dp += [x]

for item in range(0, n+1):
	for itemCount in range(n+1):
		for dist in range(len(dp[0][0])):
			dp[item][itemCount][dist] = None
dp[0][0][0] = [[]]

def isIn(item, lis):
	for x in lis:
		if item == x:
			return True
	return False

for item in range(1, n+1):
	dp[item][0][0] = [[]]
	for itemCount in range(n+1):
		for dist in range(1, len(dp[0][0])):
			a = dp[item-1][itemCount][dist]
			if a == None:
				a = []
			if dist <= d + STRIP * (itemCount+1) and itemCount > 0 and vs[item-1] <= dist:
				b = copy.deepcopy(dp[item-1][itemCount-1][dist-vs[item-1]])
#				print("For ", item, itemCount, dist)
#				print(item-1, itemCount-1, dist-vs[item-1], str(b))
				if b != None:
					for x in b:
						x += [vs[item-1]]
				else:
					b = []
			else:
				b = []

			dp[item][itemCount][dist] = a + b
			#for x in b:
			#	if not isIn(x, a):
			#		a += [x]
			#if dp[item][itemCount][dist] != []:
			#	print(item, itemCount, dist, " is now ", dp[item][itemCount][dist], a, b)

best = -1
res = []
allbest = []
for dist in range(d, len(dp[0][0])):
	for count in range(n+1):
		if len(dp[n][count][dist]) > 0:	
			val = float(dist - d) / (count + 1)
			for x in dp[n][count][dist]:
				if len(x) > 0:
					res += [str((val, dist, count, str(x), sum(x)))]
					if val >= STRIP * 0.99999:
						allbest += [x]
			best = max(best, float(dist - d) / (count + 1))

#if best == -1:
#	print("impossible")
#else:
#	print("%.8f" % best)

erased = [0] * 10000
saved = copy.deepcopy(allbest)

for xx in range(2000):
	random.shuffle(allbest)
	for x in range(len(allbest)):
		random.shuffle(allbest[x])
	era = []
	while len(allbest) > 0:
		nv = allbest[0][0]
		era += [nv]
		i = 0
		while i < len(allbest):
			k = 0
			while k < len(allbest[i]):
				if allbest[i][k] == nv:
					allbest[i] = allbest[i][:k] + allbest[i][k+1:]
					k -= 1
					if allbest[i] == []:
						allbest = allbest[:i] + allbest[i+1:]
						i -= 1
						break
				k += 1
			i += 1
	allbest = copy.deepcopy(saved)
	if len(era) < len(erased):
		erased = era

# write new testcase
count = 0
li = []
#print count, d+10
for c in vs:
	if not c in erased:
		li += [str(c)]
		count += 1
print(count, d+2*STRIP)
print("\n".join(li))
