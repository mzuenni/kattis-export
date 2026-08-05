#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define FOR(i,a,b) for (int i = (a); i < (b); i++)

int W, S, X, Y, Ws[10000][100], Ss[10000][100];

int main() {
	cin >> W >> S >> X >> Y;
	FOR(i, 0, W) FOR(j, 0, X) cin >> Ws[i][j];
	FOR(i, 0, S) FOR(j, 0, X) cin >> Ss[i][j];

	FOR(i, 0, W) {
		FOR(j, 0, X) {
			FOR(k, 0, S) Ws[i][j] = min(Ws[i][j], Y-Ss[k][j]);
			if (j != 0) cout << ' ';
			cout << Ws[i][j];
		}
		cout << endl;
	}

	return 0;
}
