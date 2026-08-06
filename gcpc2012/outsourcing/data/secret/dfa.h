#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <sstream>

using namespace std;

class Edge;
class Vertex {
public:
    int number;
    set<Edge *> inEdges;
    set<Edge *> outEdges;
};

class Edge {
public:
    Vertex *from;
    Vertex *to;
    int fromNum;
    int toNum;
    int label;
};

class Dfa {
public:
    vector<Vertex> vertices;
    map<pair<int,int>,Edge> edges;
    Dfa() {};

    string toString() {
        stringstream s;
        for(map<pair<int,int>,Edge>::iterator eit = edges.begin(); eit != edges.end(); eit++)
            s << eit->second.from->number << " " << eit->second.to->number << " " << eit->second.label << endl;
        return s.str();
    }

    // num of vertices
    int size() {
        return vertices.size();
    }

    // num of edges
    int edgeCount() {
        return edges.size();
    }

    set<Edge *> getInEdges(int n) {
        return vertices[n].inEdges;
    }

    set<Edge *> getOutEdges(int n) {
        return vertices[n].outEdges;
    }

    void addEdge(int from, int label, int to) {
        makeVertex(from);
        makeVertex(to);
        Edge &e = edges[pair<int,int> (from, label)];
        e.from = &vertices[from];
        e.to = &vertices[to];
        e.fromNum = from;
        e.toNum = to;
        e.label = label;
        vertices[from].outEdges.insert(&e);
        vertices[to].inEdges.insert(&e);
    }

    void addEdge(Edge *e) {
        addEdge(e->from->number,e->to->number,e->label);
    }

    void removeEdge(int from, int label, int to) {
        if (edges.count(pair<int,int>(from,label)) == 0) return;
        Edge &e = edges[pair<int,int> (from, label)];
        if (e.to->number != to ) return;
        e.from->outEdges.erase(&e);
        e.to->inEdges.erase(&e);
        edges.erase(pair<int,int>(from,label));
    }

    void removeEdge(Edge *e) {
        removeEdge(e->from->number,e->to->number,e->label);
    }

    private:
    // assures that vertex with number n is there
    void makeVertex(int n) {
        int s = vertices.size();
        if (n+1 > s ) {
            vertices.resize(n+1);
            for (int i = s; i < n+1; i++) vertices[i].number = i;
            for(map<pair<int,int>,Edge>::iterator eit = edges.begin(); eit != edges.end(); eit++) {
                eit->second.from = &vertices[eit->second.fromNum];
                eit->second.to = &vertices[eit->second.toNum];
            }
        }
    }
};

Dfa generateRandomDfa(int nodeCount, int labelCount, double 
edgeProbability, uint randSeed) {
     srand(randSeed);

     Dfa randDfa;

     randDfa.addEdge(nodeCount-1, 0, nodeCount-1);
     randDfa.removeEdge(nodeCount-1, 0, nodeCount-1);

     for (int i=0; i<nodeCount; i++)
         for (int c=0; c<labelCount; c++)
             if (edgeProbability*RAND_MAX < rand())
                 randDfa.addEdge(i,c,rand() % nodeCount);

     return randDfa;
}

vector<Dfa> generateAllDfas(int nodeCount, int labelCount) {
 
  vector<int> map;
  if (map.size() < nodeCount*labelCount) map.resize(nodeCount*labelCount);
  int dfaCount = 1;
  for (int i=0; i < nodeCount*labelCount; i++) {
    map[i] = 0;
    dfaCount *= nodeCount;
  }
  vector<Dfa> dfaList;
  if (dfaList.size() < dfaCount) dfaList.resize(dfaCount);

  while (dfaCount --> 0) {
    for (int i=0; i < nodeCount; i++)
      for (int c=0; c < labelCount; c++)
	    dfaList[dfaCount].addEdge(i,c,map[i*labelCount + c]);
    
    for(int i=0; i < nodeCount*labelCount; i++) {
      map[i] = (map[i] + 1) % nodeCount;
      if (map[i] != 0) break;
    }
  }

  return dfaList;
}

void modify(Dfa &d, int c) {
    if (c == 0) return;

    int final = d.size()-1;
    while (c --> 1) {
        // choose state to clone
        // dont clone the final state!, so choose a number smaller and then shift
        int orig = rand() % (d.size()-1);
        if (orig >= final) orig++;

        int clone = d.size();
        set<Edge *> edges = d.getInEdges(orig);
        for (set<Edge *>::iterator eit = edges.begin(); eit != edges.end(); eit++) {
            if (rand() % 2) d.addEdge((*eit)->fromNum,(*eit)->label,clone);
        }
        edges = d.getOutEdges(orig);
        for (set<Edge *>::iterator eit = edges.begin(); eit != edges.end(); eit++) {
            d.addEdge(clone,(*eit)->label,(*eit)->toNum);
        }
    }
    set<Edge *> edges = d.getInEdges(final);
    int clone = d.size();
    for (set<Edge *>::iterator eit = edges.begin(); eit != edges.end(); eit++) {
        d.addEdge((*eit)->fromNum,(*eit)->label,clone);
    }
    edges = d.getOutEdges(final);
    for (set<Edge *>::iterator eit = edges.begin(); eit != edges.end(); eit++) {
        d.addEdge(clone,(*eit)->label,(*eit)->toNum);
    }
}
