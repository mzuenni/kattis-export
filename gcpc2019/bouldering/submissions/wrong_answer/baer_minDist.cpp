/**
 * Authpr: Michael Baer
 * @EXPECTED_RESULT@ WRONG_ANSWER
 * Idea: Dijkstra for shortest path, but only take edges where remaining stamina is enough
 */
#include <bits/stdc++.h>

using namespace std;

const double oo = 0x3f3f3f3f3f3f3f3f;
int main() {
	int h, w, r, c;
	cin >> h >> w >> r >> c;
	vector<string> v(h);
	for (auto & s : v) cin >> s;
	vector<vector<double>> dist(h, vector<double>(w, oo));
	vector<vector<bool>> done(h, vector<bool>(w, false));
	int sh = -1, sw = -1;
	for (int hh = h-1; hh >= 0; hh--) {
		for (int ww = 0; ww < w; ww++) {
			if (v[hh][ww] != '.') {
				sh = hh;
				sw = ww;
				goto weiter1;
			}
		}
	}
weiter1:
	int eh = -1, ew = -1;
	for (int hh = 0; hh < h; hh++) {
		for (int ww = 0; ww < w; ww++) {
			if (v[hh][ww] != '.') {
				eh = hh;
				ew = ww;
				goto weiter2;
			}
		}
	}
weiter2:
	using T = tuple<double,int,int,int>;
	set<T> pq;
	pq.insert(make_tuple(0, sh, sw, c - (v[sh][sw]-'0')));
	while (pq.size()) {
		T cur = *pq.begin();
		pq.erase(pq.begin());
		if (done[get<1>(cur)][get<2>(cur)]) continue;
		done[get<1>(cur)][get<2>(cur)] = true;
		for (int dh = -5; dh <= 5; dh++) for (int dw = -5; dw <= 5; dw++) if (dh * dh + dw * dw <= r * r) {
			int nh = get<1>(cur)+dh;
			int nw = get<2>(cur)+dw;
			if (nh >= 0 && nh < h && nw >= 0 && nw < w && v[nh][nw] != '.') {
				double nd = get<0>(cur) + sqrt(dw*dw + dh*dh);
				if (nd < dist[nh][nw] && get<3>(cur) - (v[nh][nw]-'0') >= 0) {
					pq.insert(make_tuple(nd, nh, nw, get<3>(cur) - (v[nh][nw]-'0')));
					dist[nh][nw] = nd;
				}
			}
		}
	}
	if (dist[eh][ew] == oo) {
		printf("impossible\n");
	} else {
		printf("%.7f\n", dist[eh][ew]);
	}
}
