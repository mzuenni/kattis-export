import random
import copy

random.seed(42)

class Graph():
	def __init__(self, edges, start=None):
		self.startNode = start
		a,b,c=zip(*edges)
		self.nodes = max(max(a),max(b)) + 1
		self.edges = edges
		
	def write(self, f):
		if self.startNode != None:
			f.write("%d %d\n" % (self.nodes, self.startNode+1))
		else:
			f.write("%d\n" % self.nodes)
		el = [[] for _ in range(self.nodes)]
		for e in self.edges:
			el[e[0]] += [(e[1], e[2])]
			el[e[1]] += [(e[0], e[2])]
		for n in range(self.nodes):
			for i in range(len(el[n])):
				if el[n][i][1] < 0 or el[n][i][1] >= 26:
					print("Error with %d" % el[n][i][1])
			eParts = ["%c %d" % (ord('A') + el[n][i][1], el[n][i][0] + 1) for i in range(len(el[n]))]
			random.shuffle(eParts)
			f.write("%d %s\n" % (len(el[n]), " ".join(eParts)))

def create_test(name, level, karte, res):
	with open("../data/secret/%s.in" % name, "w") as f:
		f.write("--Level--\n")
		level.write(f)
		f.write("---Map---\n")
		karte.write(f)
	with open("../data/secret/%s.ans" % name, "w") as f:
		f.write(res + "\n")
		if res == "U": # now print the mapping
			f.write(" ".join([str(i+1) for i in range(level.nodes)]) + "\n")
	
MAX_N = 1000

# cycles 
def cycle(n, d):
	return list(zip(range(n), range(1,n), list(range(d))*n)) + [(n-1, 0, d-1)]

# tree
def tree(cur, degree, depth, last, startidx):
	edges = []
	if depth == 0:
		return ([], startidx)
	for i in range(degree):
		if i != last:
			edges += [(cur, startidx, i)]
			startidx += 1
			a = tree(startidx-1, degree, depth - 1, i, startidx)
			edges += a[0]
			startidx = a[1]
	return (edges, startidx)

def treeinit(degree, depth):
	return [(0, 1, 0)] + tree(1, degree, depth, 0, 2)[0]

def fully8():
	edges = []
	for i in range(7):
		edges += [(7, i, i)]
		for k in range(1,4):
			a1 = (i+k) % 7
			b1 = (i-k+7) % 7
			edges += [(a1, b1, i)]
	return edges

def randomGraph(n, diff=False):
	edges = []
	ns = [[] for _ in range(n)]
	for i in range(1, n):
		while True:
			nx = random.randint(0, i-1)
			x = random.randint(0, 25)
			if x not in ns[nx]:
				edges += [(i, nx, x)]
				ns[nx] += [x]
				ns[i] += [x]
				break
	for i in range(n * n):
		a = random.randint(0, n-1)
		b = random.randint(0, n-1)
		c = random.randint(0, 25)
		if a == b:
			continue
		if c in ns[a] or c in ns[b]:
			continue
		
		edges += [(a, b, c)]
		ns[a] += [c]
		ns[b] += [c]
	edges2 = copy.deepcopy(edges)
	if diff == True:
		while True:
			a = random.randint(0, n-1)
			b = random.randint(0, n-1)
			c = random.randint(0, 25)
			if a == b:
				continue
			if c in ns[a] or c in ns[b]:
				continue
			
			edges2 += [(a, b, c)]
			ns[a] += [c]
			ns[b] += [c]
			break
	return (edges, edges2)
		
def randomGraphA(n):
	edges = []
	n2 = n // 2
	ns = [[] for _ in range(n2)]
	for i in range(1, n2):
		while True:
			nx = random.randint(0, i-1)
			x = random.randint(0, 25)
			if x not in ns[nx]:
				edges += [(i, nx, x)]
				edges += [(i+n2, nx+n2, x)]
				ns[nx] += [x]
				ns[i] += [x]
				break
	for i in range(n2 * n2):
		a = random.randint(0, n2-1)
		b = random.randint(0, n2-1)
		c = random.randint(0, 25)
		if a == b:
			continue
		if c in ns[a] or c in ns[b]:
			continue
		
		edges += [(a, b, c), (a+n2, b+n2, c)]
		ns[a] += [c]
		ns[b] += [c]
	# add connecting edge
	for i in range(n2):
		if len(ns[i]) < 26:
			for x in range(26):
				if x not in ns[i]:
					edges += [(i, i+n2, x)]
					return edges
	print("Failed")

if True:
	# Level has the same size as the map
	create_test("10-cycle_2_2", Graph(cycle(2,2),0), Graph(cycle(2,2)), "A")
	create_test("11-cycle_4_4", Graph(cycle(4,2),0), Graph(cycle(4,2)), "A")
	create_test("12-cycle_samesize", Graph(cycle(MAX_N,2),0), Graph(cycle(MAX_N,2)), "A")
	# Level has half the size of the map
	create_test("13-cycle_2_4", Graph(cycle(2,2),0), Graph(cycle(4,2)), "N")
	create_test("14-cycle_4_8", Graph(cycle(4,2),0), Graph(cycle(8,2)), "N")
	create_test("15-cycle_halfsize", Graph(cycle(MAX_N//2,2),0), Graph(cycle(MAX_N,2)), "N")
	# Level has double the size of the map
	create_test("16-cycle_4_2", Graph(cycle(4,2),0), Graph(cycle(2,2)), "N")
	create_test("17-cycle_8_4", Graph(cycle(8,2),0), Graph(cycle(4,2)), "N")
	create_test("18-cycle_doublesize", Graph(cycle(MAX_N,2),0), Graph(cycle(MAX_N//2,2)), "N")
	# 2 cycles, but a single extending node to make unique
	create_test("19-cycle_samesize", Graph(cycle(MAX_N-2,2)+[(MAX_N//2,MAX_N-2,2)],0), Graph(cycle(MAX_N-2,2)+[(MAX_N//2,MAX_N-2,2)]), "U")
	# simple trees
	create_test("30-fully8", Graph(fully8(), 3), Graph(fully8()), "U")
	
	create_test("31-tree-1", Graph(treeinit(3, 2), 0), Graph(treeinit(3, 2)), "U")
	create_test("31-tree-2", Graph(treeinit(3, 3), 0), Graph(treeinit(3, 3)), "U")
	create_test("31-tree-3", Graph(treeinit(26, 1), 0), Graph(treeinit(26, 1)), "U")
	create_test("31-tree-4", Graph(treeinit(26, 2), 0), Graph(treeinit(26, 2)), "U")
	create_test("31-tree-5", Graph(treeinit(9, 3), 0), Graph(treeinit(9, 3)), "U")
	create_test("31-tree-6", Graph(treeinit(3, 6), 0), Graph(treeinit(3, 6)), "U")
	
	x, y = randomGraph(10)
	create_test("32-rnd-1", Graph(copy.deepcopy(x), 0), Graph(copy.deepcopy(y)), "U")
	x, y = randomGraph(20)
	create_test("32-rnd-2", Graph(copy.deepcopy(x), 0), Graph(copy.deepcopy(y)), "U")
	x, y = randomGraph(100)
	create_test("32-rnd-3", Graph(copy.deepcopy(x), 0), Graph(copy.deepcopy(y)), "U")
	x, y = randomGraph(1000)
	create_test("32-rnd-4", Graph(copy.deepcopy(x), 0), Graph(copy.deepcopy(y)), "U")
	
	x, y = randomGraph(1000, True)
	create_test("32-rnd-4", Graph(copy.deepcopy(x), 0), Graph(copy.deepcopy(y)), "N")
	x, y = randomGraph(1000, True)
	create_test("32-rnd-4", Graph(copy.deepcopy(x), 0), Graph(copy.deepcopy(y)), "N")
	create_test("32-rnd-4", Graph(copy.deepcopy(y), 0), Graph(copy.deepcopy(x)), "N")
	
	x = randomGraphA(4)
	create_test("33-rndA-1", Graph(x, 0), Graph(x), "A")
	x = randomGraphA(10)
	create_test("33-rndA-2", Graph(x, 0), Graph(x), "A")
	x = randomGraphA(100)
	create_test("33-rndA-3", Graph(x, 0), Graph(x), "A")
	x = randomGraphA(500)
	create_test("33-rndA-4", Graph(x, 0), Graph(x), "A")
	x = randomGraphA(1000)
	create_test("33-rndA-5", Graph(x, 0), Graph(x), "A")
#	create_test("30-fully_5", Graph(fully(5),0), Graph(fully(5)), "U")
#	create_test("30-fully_5_2", Graph(fully(5),0), Graph(fully(5,offset=1)), "N")
#	create_test("30-fully_26", Graph(fully(26),0), Graph(fully(26)), "U")
#	create_test("30-fully_26_2", Graph(fully(26),0), Graph(fully(26,offset=7)), "U")
