#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <algorithm>

#include "dfa.h"

using namespace std;

int main() {
    int nodeCount = 100;
    int labelCount = 75;
    int tc = 5;

		cout << tc << endl;

		while (tc > 0) {
      int nc1 = nodeCount + (rand() % nodeCount) - (nodeCount / 2);
      int nc2 = nodeCount + (rand() % nodeCount) - (nodeCount / 2);
      int lc1 = labelCount + (rand() % labelCount) - (labelCount / 2);
      int lc2 = labelCount + (rand() % labelCount) - (labelCount / 2);
      double edgeProbability = (double)rand() / (double)RAND_MAX;

      Dfa dfa1 = generateRandomDfa(nc1, lc1, edgeProbability, rand());
      Dfa dfa2 = generateRandomDfa(nc2, lc2, edgeProbability, rand());

			dfa1.addEdge(0, 0, dfa1.size()-1);
			dfa2.removeEdge(0, 0, dfa2.size()-1);

      cout << dfa1.edgeCount() << " " << dfa1.size() << " " << lc1 << " " << dfa2.edgeCount() << " " << dfa2.size() << " " << lc2 << endl;
      cout << dfa1.toString();
      cout << dfa2.toString();

			tc--;
    }

    return 0;
}
