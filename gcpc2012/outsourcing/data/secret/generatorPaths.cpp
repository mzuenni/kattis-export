#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <algorithm>

#include "dfa.h"

using namespace std;

void generatePath(Dfa &dfa, int nodeCount, int transitionSymbol) {
		for (int i=0; i < nodeCount-1; i++) dfa.addEdge(i,transitionSymbol,i+1);
}

int main() {
    int nodeCount = 50;
    int transitionSymbol = 25;
    int tc = 10;
		
		srand(0);

		cout << tc << endl;

		for (int i=0; i < tc; i++) {
      int nc = nodeCount + (rand() % nodeCount) - (nodeCount / 2);
      int ts1 = transitionSymbol + (rand() % transitionSymbol) - (transitionSymbol / 2);
      int ts2 = transitionSymbol + (rand() % transitionSymbol) - (transitionSymbol / 2);

      Dfa dfa1;
      generatePath(dfa1, nc, ts1);
      cout << dfa1.edgeCount() << " " << dfa1.size() << " " << (ts1+1) << " ";
      Dfa dfa2;
      if (i < tc/2) {
      	generatePath(dfa2, nc, ts1);
      	cout << dfa2.edgeCount() << " " << dfa2.size() << " " << (ts1+1) << endl;
      } else {
      	generatePath(dfa2, nc, ts2);
      	cout << dfa2.edgeCount() << " " << dfa2.size() << " " << (ts2+1) << endl;
      }

			cout << dfa1.toString();
      cout << dfa2.toString();
    }

    return 0;
}
