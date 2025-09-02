#!/bin/python2

import random
import itertools

random.seed(42)

maxN = 60
maxA = 1000

numTests = 3

tests = [
	{"n": 5, "d": 20, "target": 110, "count": 3, "mind": 11},
	{"n": 10, "d": 50, "target": 110, "count": 2, "mind": 11},
	{"n": 30, "d": 200, "target": 1000, "count": 2, "mind": 11},
	{"n": 60, "d": 50, "target": 1000, "count": 2, "mind": 11},
	{"n": 60, "d": 1000, "target": 1000, "count": 3, "mind": 11},
	
	{"n": 30, "d": 200, "target": 1000, "count": 2, "mind": 195},
	{"n": 60, "d": 1000, "target": 1000, "count": 3, "mind": 300}
]

tc = 0
for test in tests:
	for _ in range(test["count"]):
		with open("secret/random_%02d_%d.in" % (tc, test["n"]), "w") as tfile:
			tfile.write(str(test["n"]) + " " + str(test["target"]) + "\n")
			for n in range(test["n"]):
				tfile.write(str(random.randint(test["mind"], test["d"])) + "\n")
		tc += 1
