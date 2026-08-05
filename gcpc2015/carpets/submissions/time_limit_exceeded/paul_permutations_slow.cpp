#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
#define sz(c) int((c).size())
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define xx first
#define yy second

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int W, H, c;
	cin >> W >> H >> c;
	vector<pii> tiles;
	FOR(i,0,c) {
		int a, wa, ha; cin >> a >> wa >> ha;
		FOR(j,0,a) tiles.push_back({wa,ha});
	}
	int n = sz(tiles);
	sort(begin(tiles),end(tiles));
	bool res = false;
	do {
		FOR(mask,0,1 << n) {
			FOR(i,0,n) if (mask & (1 << i)) swap(tiles[i].xx,tiles[i].yy);
			vector<vector<bool>> a(H,vector<bool>(W));
			int k = 0;
			bool ok = true;
			FOR(i,0,H) FOR(j,0,W) if (ok && !a[i][j]) {
				if (i + tiles[k].xx > H || j + tiles[k].yy > W) {
					ok = false;
					break;
				}
				FOR(di,0,tiles[k].xx) FOR(dj,0,tiles[k].yy) {
					if (a[i+di][j+dj]) {
						ok = false;
						break;
					}
					a[i+di][j+dj] = true;
				}
				k++;
			}
			if (ok) {
				res = true;
				break;
			}
			FOR(i,0,n) if (mask & (1 << i)) swap(tiles[i].xx,tiles[i].yy);
		}
		if (res) break;
	} while (next_permutation(begin(tiles),end(tiles)));
	
	if (res) cout << "yes" << endl;
	else cout << "no" << endl;;
}

