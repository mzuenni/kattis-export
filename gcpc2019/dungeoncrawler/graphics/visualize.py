import sys
import networkx as nx
import matplotlib.pyplot as plt

inFile = sys.argv[1]
ansFile = sys.argv[2]
outFile = sys.argv[3]

artifacts = ["sword", "holygrail", "ring", "scepterofawesomeness", "mightydagger", "bootsofswiftness"]

def initArtifacts(n):
	global artifacts
	while len(artifacts) < n:
		artifacts += ["A"+ str(len(artifacts))]

def initArtifactsSlow(n):
	global artifacts
	ars = [ord('a')] * 10
	while len(artifacts) < n:
		artifacts += ["".join(map(chr, ars))]
		k = len(ars)-1
		ars[k] += 1
		while ars[k] > ord('z'):
			ars[k] = ord('a')
			k -= 1
			ars[k] += 1

with open(inFile) as inf:
	lvlInput = inf.readlines()

with open(ansFile) as inf:
	answer = inf.readlines()


if lvlInput[0] == "--Level:infinite--":
	print("Level is infinite. Aborting")
	sys.exit(0)


n, pos = map(int, lvlInput[1].strip().split(" "))
pos -= 1

if n > 40:
	print("Level too large. Aborting")
	sys.exit(0)

def genGraph(n, lines, shift, printLabels):
	Level = nx.MultiGraph()
	initArtifacts(40)

	edgelabels = dict()
	for i in range(n):
		ps = lines[i].strip().split(" ")
		ns = int(ps[0])
		for nei in range(ns):
			label = ps[2*nei + 1]
			target = int(ps[2*nei + 2]) - 1
			Level.add_edge(i, target)
			edgelabels[(i, target)] = label

	if printLabels:
		labels={i:artifacts[i] for i in range(n)}
	else:
		labels=None
	pos=nx.spring_layout(Level)
	for k, v in pos.items():
		v[0] = v[0] + shift
	nx.draw_networkx(Level, ax=None, pos=pos, labels=labels)
	nx.draw_networkx_edge_labels(Level, pos=pos, edge_labels=edgelabels)
	plt.axis("off")

genGraph(n, lvlInput[2:2+n], 0, False)
n2 = int(lvlInput[2+n+1])
genGraph(n2, lvlInput[2+n+2:], 2, True)
if answer[0].strip() == "U":
	plt.text(0, 0, "unique answer")
elif answer[0].strip() == "N":
	plt.text(0, 0, "different")
elif answer[0].strip() == "A":
	plt.text(0, 0, "ambiguous")
#plt.show()

plt.savefig(outFile)
