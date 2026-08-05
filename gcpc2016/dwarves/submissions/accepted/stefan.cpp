//Author: Stefan Toman

#include <iostream>
#include <map>
#include <vector>
#include <queue>

using namespace std;

map<string, int> names;
int names_count = 0;
int dwarf(string name) {
	if(names[name] == 0) names[name] = ++names_count;
	return names[name] - 1;
}

int main() {
        string trash;
	int n;
	cin >> n;
	vector< vector<int> > smaller(2*n);
	for(int i = 0; i < n; i++) {
		string namea, nameb, relation;
		cin >> namea >> relation >> nameb;
		if(relation == "<") {
			trash = namea;
			namea = nameb;
			nameb = trash;
		}
		smaller[dwarf(namea)].push_back(dwarf(nameb));
	}
	bool liar = false;
	for(int i = 0; i < names_count && !liar; i++) {
		vector<bool> visited(names_count, false);
		queue<int> q;
		q.push(i);
		while(!q.empty() && !liar) {
			for(auto j: smaller[q.front()]) {
				if(j == i) liar = true;
				if(!visited[j]) {
					visited[j] = true;
					q.push(j);
				}
			}
			q.pop();
		}
	}
	cout << (liar ? "impossible" : "possible") << endl;
	return 0;
}
