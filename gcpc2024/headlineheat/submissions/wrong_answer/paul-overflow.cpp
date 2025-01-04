#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

const int N = 2e6 + 10, K = 3, C = 27;
using H = array<int,K>;

const H P = {i64(1e9) + 7, i64(1e9) + 9, i64(1e9) + 21};
const H B = {123456789, 987654321, 543212345};

H &operator+=(H &a, const H &b) {
    for (int k = 0; k < 3; k++) a[k] = (a[k] + b[k]) % P[k];
    return a;
}

H operator-=(H &a, const H &b) {
    for (int k = 0; k < 3; k++) a[k] = (a[k] - b[k] + P[k]) % P[k];
    return a;
}

struct aho_corasick {
	int id(char c) { return c == ' ' ? 0 : c-'a'+1; } // transform character to number in [0,K-1]

	int M = 1;
	vector<int> suf, par, last;
    vector<H> hash;
	vector<array<int,C>> go;

	aho_corasick(const vector<pair<string,H>> &words): suf(N), par(N), last(N), hash(N), go(N) {
		for (auto &g: go) g = {};
        for (auto &h: hash) h = {};
		for (const auto &[s, h]: words) {
			int k = 0;
			for (char c_: s) {
				int c = id(c_);
				if (go[k][c] == 0) {
					go[k][c] = M;
					last[M] = c;
					par[M++] = k;
				}
				k = go[k][c];
			}
			hash[k] += h;
		}

		queue<int> q;
		q.push(0);
		while (!q.empty()) {
			int k = q.front();
			q.pop();
			if (par[k] != 0) suf[k] = go[suf[par[k]]][last[k]];
			for (int c = 0; c < C; c++) {
				if (go[k][c] == 0) go[k][c] = go[suf[k]][c];
				else q.push(go[k][c]);
			}
			hash[k] += hash[suf[k]];
		}
	}

	H match(string s) {
		int k = 0;
		H res = {};
		for (char c_: s) {
			k = go[k][id(c_)];
			res += hash[k];
		}
		return res;
	}
};

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    string s;
    getline(cin, s);

    vector<pair<string,H>> names(n, {"", {}});
    for (auto &[s, _]: names) getline(cin, s);

    H cur = {1, 1, 1};
    while (m--) {
        for (int k = 0; k < K; k++) {
            cur[k] = cur[k] * B[k] % P[k];
        }

        int a, b;
        cin >> a >> b;
        a--, b--;

        names[a].second -= cur;
        names[b].second += cur;
    }

    aho_corasick A(names);

    getline(cin, s);
    for (int i = 0; i < k; i++) {
        getline(cin, s);
        H res = A.match(s);
        bool ok = !res[0] && !res[1] && !res[2];
        cout << (ok ? "yes" : "no") << '\n';
    }
}
