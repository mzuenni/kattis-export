//Author: Stefan Toman

#include <iostream>
#include <map>
#include <vector>
#include <queue>

using namespace std;

int main() {
	int n, m;
	cin >> n >> m;
	vector< map <char, vector<int> > > doors(n);
	for(int i = 0; i < m; i++) {
		int a, b;
		char l;
		cin >> a >> b >> l;
		doors[a-1][l].push_back(b-1);
		doors[b-1][l].push_back(a-1);
	}
	string seq;
	cin >> seq;
	vector<double> p(n);
	p[0] = 100.0;
	for(int i = 0; i < seq.size(); i++) {
		vector<double> newp(n);
		for(int j = 0; j < n; j++) {
			if(j < n-1 && doors[j][seq[i]].size() > 0) {
				for(int next: doors[j][seq[i]]) {
					newp[next] += p[j] / doors[j][seq[i]].size(); 
				}
			}
			else {
				newp[j] += p[j];
			}
		}
		p = newp;
	}
	cout << p[n-1] << endl;
	return 0;
}