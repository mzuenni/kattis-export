#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using vl = vector<ll>;

#define FOR(i,a,b) for (int i = a; i < (b); i++)

ll n;
vector<map<char, ll>> karte;
vector<string> out;
vector<int> vis;
map<string, int> ids;

struct state {
	vector<ll> mapping;
	vector<int> vis;
	stack<int> curM;
	state(int n) : mapping(n, -1), vis(n) {}
};
deque<state> poss;

int toid(const string & s) {
	auto it = ids.find(s);
	if (it == ids.end()) {
		int k = ids.size();
		ids[s] = k;
		return k;
	}
	return it->second;
}

void write(const string & s) {
	cout << s << endl;
	cout.flush();
}
void dfs(int nn, string s, char last) {
	vis[nn] = true;
	if (poss.size() == 0) {
		cerr << "no more poss" << endl;
		write("R no");
		exit(0);
	}
	for (char c : s) {
		if (c == last) continue; // skip where we came from
		cout << "W " << c << endl;
		cout.flush();
		int c1;
		string artifact, s1;
		cin >> artifact >> s1;
		c1 = toid(artifact);
		sort(s1.begin(), s1.end());
		if (c1 >= n) {
			// impossible this big numbers
			cerr << "num too high" << endl;
			write("R no");
			exit(0);
		}
		auto it = poss.begin();
		bool cycle = false;
		while (it != poss.end()) {
			ll newM = karte[it->curM.top()][c];
			it->curM.push(newM);
			if (s1 != out[newM]) { // strings match
				it = poss.erase(it);
				continue;
			} else {
				if (it->mapping[c1] != -1) {
					// already mapped
					// but not in this instance
					if (it->mapping[c1] != newM) {
						it = poss.erase(it);
						continue;
					}
					cycle = true;
				} else {
					// unmapped
					if (it->vis[newM]) { // but alreasdy visited in map
						it = poss.erase(it);
						continue;
					}
					it->vis[newM] = true;
					it->mapping[c1] = newM;
				}
			}
			it++;
		}
		if (!cycle) {
			dfs(c1, s1, c);
		}
		for (auto & st : poss) st.curM.pop();
		// return
		cout << "W " << c << endl;
		cout.flush();
		cin >> artifact >> s1; // we already know what to find here
	}
}

int main() {
	cin >> n;
	karte.resize(n);
	out.resize(n);
	vis.resize(n);
	FOR(i,0,n) {
		ll k;
		cin >> k;
		FOR(j, 0, k) {
			char t;
			ll m;
			cin >> t >> m;
			karte[i][t] = m-1;
			out[i] += t;
		}
		sort(out[i].begin(), out[i].end());
	}
	ll cur;
	string tmp;
	cin >> tmp;
	cur = toid(tmp);
	string curs;
	cin >> curs;
	sort(curs.begin(), curs.end());
	FOR(i,0,n) if (out[i] == curs) {
		state st(n);
		st.mapping[cur] = i;
		st.curM.push(i);
		poss.push_back(st);
	}
	dfs(cur, curs, -1);
	if (poss.size() > 1) {
		cout << "R ambiguous" << endl;
	} else {
		cout << "R " << poss.begin()->mapping[cur]+1 << endl;
	}
	cout.flush();
}
