#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <algorithm>

#include "dfa.h"

using namespace std;

int main() {
    int nodeCount = 4;
    int labelCount = 2;
    int numcases = 100;
    vector<Dfa> dfas = generateAllDfas(nodeCount,labelCount);

    cout << numcases << endl;

    while (numcases --> 0) {
      int i,j;
      i = rand() % dfas.size();
      j = rand() % dfas.size();
      cout << dfas[i].edgeCount() << " " << nodeCount << " " << labelCount << " " << dfas[j].edgeCount() << " " << nodeCount << " " << labelCount << endl;
      cout << dfas[i].toString();
      cout << dfas[j].toString();
    }

    return 0;
}
