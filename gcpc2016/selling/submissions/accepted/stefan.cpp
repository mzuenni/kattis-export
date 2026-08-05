//Author: Stefan Toman

#include <iostream>
#include <map>
#include <vector>
#include <queue>

using namespace std;

int main() {
	int c, m;
	cin >> c >> m;
	vector< vector<int> > p(m), r(m+1, vector<int>(c+1));
	for(int i = 0; i < m; i++) {
		for(int j = 0; j < c; j++) {
			int t;
			cin >> t;
			p[i].push_back(t);
		}
	}
	for(int i = 0; i < m; i++) {
		for(int j = 0; j <= c; j++) {
			r[i+1][j] = r[i][j];
			for(int k = 1; k <= j; k++) {
				if(r[i+1][j] < r[i][j-k] + p[i][k-1]) {
					r[i+1][j] = r[i][j-k] + p[i][k-1];
				}
			}
		}
	}
	cout << r[m][c] << endl;
	return 0;
}