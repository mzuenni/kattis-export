#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <algorithm>

#include "dfa.h"

using namespace std;

int main() {
    int modCountMax = 100;
    int tc = 10;

    cout << tc << endl;

	while (tc > 0) {
      Dfa dfa1;
      dfa1.addEdge(0,1,1);
      dfa1.addEdge(0,0,2);
      dfa1.addEdge(1,0,3);
      dfa1.addEdge(1,1,1);
      dfa1.addEdge(2,0,3);
      dfa1.addEdge(2,1,2);

      Dfa dfa2;
      dfa2.addEdge(0,0,1);
      dfa2.addEdge(0,1,1);
      dfa2.addEdge(0,3,3);
      dfa2.addEdge(0,2,2);
      dfa2.addEdge(1,0,5);
      dfa2.addEdge(1,1,1);
      dfa2.addEdge(2,0,4);
      dfa2.addEdge(2,1,2);
      dfa2.addEdge(2,2,2);
      dfa2.addEdge(2,3,2);
      dfa2.addEdge(3,0,4);
      dfa2.addEdge(3,1,3);
      dfa2.addEdge(3,2,3);
      dfa2.addEdge(3,3,3);

      int mc1 = (rand() % modCountMax);
      int mc2 = (rand() % modCountMax);

      modify(dfa1, mc1);
      modify(dfa2, mc2);

      cout << dfa1.edgeCount() << " " << dfa1.size() << " " << 4 << " " << dfa2.edgeCount() << " " << dfa2.size() << " " << 4 << endl;
      cout << dfa1.toString();
      cout << dfa2.toString();
      cout << endl;

			tc--;
    }

    return 0;
}
