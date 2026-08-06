#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <algorithm>

#include "dfa.h"

using namespace std;

int main() {
    int nodeCount = 100;
    int labelCount = 25;
    int modCount = 50;
    int tc = 5;

		cout << tc << endl;

		while (tc > 0) {
      int nc = nodeCount + (rand() % nodeCount) - (nodeCount / 2);
      int lc = labelCount + (rand() % labelCount) - (labelCount / 2);
      double edgeProbability = (double)rand() / (double)RAND_MAX;

      Dfa dfa1 = generateRandomDfa(nc, lc, edgeProbability, tc);
      Dfa dfa2 = generateRandomDfa(nc, lc, edgeProbability, tc);

			int mc1 = modCount + (rand() % modCount) - (modCount / 2);
			int mc2 = modCount + (rand() % modCount) - (modCount / 2);

			modify(dfa1, mc1);
			modify(dfa2, mc2);

      cout << dfa1.edgeCount() << " " << dfa1.size() << " " << lc << " " << dfa2.edgeCount() << " " << dfa2.size() << " " << lc << endl;
      cout << dfa1.toString();
      cout << dfa2.toString();
      cout << endl;

			tc--;
    }

    return 0;
}
