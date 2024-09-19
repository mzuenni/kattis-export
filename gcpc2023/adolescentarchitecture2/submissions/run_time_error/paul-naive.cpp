#include <cstring>
#include <cmath>
#include <iostream>
#include <set>
#include <tuple>
#include <vector>
using namespace std;

double scale[3][3] = {{1, sqrt(2), sqrt(3)}, {0.5, 1, sqrt(6)-sqrt(2)}, {1/sqrt(12), sqrt(12)-3, 1}};

bool fit(int j, int b, int i, int a) {
	return b < scale[i][j] * a;
}

const int N = 2222;
int dp[3][N];

int g(int i, int a) {
	if (dp[i][a] != -1) return dp[i][a];
	
	set<int> reach;
	for (int j = 0; j < 3; j++) {
		for (int b = 1; fit(j, b, i, a); b++) {
			reach.insert(g(j, b));
		}
	}

	dp[i][a] = 0;
	while (reach.count(dp[i][a])) dp[i][a]++;
	return dp[i][a];
}

int main() {
	memset(dp, -1, sizeof dp);

	int n; cin >> n;
	vector<pair<int,int>> shapes(n);
	for (auto &[i,a]: shapes) {
		string s;
		cin >> s >> a;
		i = s == "circle" ? 0 : s == "square" ? 1 : 2;
	}

	int G = 0;
	for (auto [i,a]: shapes) G ^= g(i, a);

	int res = 0;
	for (auto [i,a]: shapes) {
		for (int j = 0; j < 3; j++) {
			for (int b = 1; fit(j, b, i, a); b++) {
				if ((G ^ g(i, a) ^ g(j, b)) == 0) res++;
			}
		}
	}
	cout << res << '\n';
}
