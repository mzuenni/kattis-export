#include <iostream>
#include <limits>
#include <list>
#include <string>
#include <cmath>
using namespace std;

struct arc{
	int start;
	int end;
	double weight;
};

bool hasNegativeCycle(int numNodes, list< arc> & arcs){
	for(int v = 0; v < numNodes; v++){
		double dist[numNodes];
		const double inf = numeric_limits<double>::infinity();
		fill_n(dist, numNodes, inf);
		dist[v] = 0.0;
		for(int i = 0; i < numNodes - 1; i++){
			for(arc a : arcs){
				double d = dist[a.start] + a.weight;
				if(d < dist[a.end]){
					dist[a.end] = d;
				}
			}
		}
		for(arc a : arcs){
			if(dist[a.start] + a.weight < dist[a.end]){
				return true;
			}
		}
	} 
	return false;
}

int main(){
	int numNodes, numArcs;
	cin >> numNodes >> numArcs;
	list<arc> arcs;
	for(int j = 0; j < numArcs; j++){
		int s, e;
		double w;
		cin >> s >> e >> w;
		arcs.push_back(arc{s-1, e-1, -log(w)});
	}
	string reply = hasNegativeCycle(numNodes, arcs) ? "inadmissible" : "admissible";
	cout << reply << endl;
	return 0;
}
