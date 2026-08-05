#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;
#define FOR(i,a,b) for (int i = (a); i < (b); i++)

int carpets[20][2], W, H, C, c, a, w, h, filled;
bool floo[100][100], used[20];

bool bt(int x, int y) {
	if (filled == W*H) return true;
	FOR(x, 0, W) FOR(y, 0, H) {
		if (!floo[x][y]) FOR(cur, 0, C) {
			if (used[cur]) continue;
			FOR(rot, 0, 2) {
				if (x + carpets[cur][rot] > W || y + carpets[cur][1-rot] > H) continue;
				bool allFree = true;
				FOR(i, 0, carpets[cur][rot]) FOR(j, 0, carpets[cur][1-rot]) if (floo[x+i][y+j]) allFree = false;
				if (allFree) {
					FOR(i, 0, carpets[cur][rot]) FOR(j, 0, carpets[cur][1-rot]) floo[x+i][y+j] = true;
					used[cur] = true;
					filled += carpets[cur][0] * carpets[cur][1];
					if (bt(x+carpets[cur][rot], y)) return true;
					filled -= carpets[cur][0] * carpets[cur][1];
					used[cur] = false;
					FOR(i, 0, carpets[cur][rot]) FOR(j, 0, carpets[cur][1-rot]) floo[x+i][y+j] = false;
				}
				if (carpets[cur][0] == carpets[cur][1]) break;
			}
		}
	}
	return false;
}

int main() {
	cin >> W >> H >> c;
	FOR(i, 0, c) {
		cin >> a >> w >> h;
		FOR(j, 0, a) {
			carpets[C][0] = w;
			carpets[C][1] = h;
			C++;
		}
	}
	cout << (bt(0,0) ? "yes" : "no") << endl;
	return 0;
}
