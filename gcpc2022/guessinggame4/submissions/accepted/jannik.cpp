#include <vector>
#include <algorithm>
#include <iostream>
#include <cstring>

using namespace std;

using ll = long long;
using vll = vector<ll>;

#define sz(a) ll((a).size())
#define all(a) (a).begin(),(a).end()


constexpr ll MAXN = 2000000;

vll adj[MAXN][2]; // input: graph and rev. graph
ll ccomp, comp[MAXN]; // output: component of each node
vll st; // temp: stack
ll prefix[10], ngames[10];
template<ll dir>
void dfs(ll n, ll c) {
	if (comp[n] != -1) return;
	comp[n] = c;
	for(ll j : adj[n][dir]) dfs<dir>(j, c);
	if (!dir) st.push_back(n);
}
void kosaraju(ll n) {
	memset(comp, -1, sizeof(comp));
	st.clear();
	for (ll i = 0; i < n; ++i) dfs<0>(i, 0);
	reverse(all(st));
	memset(comp, -1, sizeof(comp));
	ccomp = 0;
	for (ll i = 0; i < n; ++i)
		if (comp[st[i]] == -1)
			dfs<1>(st[i], ccomp++);
}

struct Var {
	ll v;
	Var(ll a = 0) : v(2*a) { }
	Var operator!() const { Var r = *this; r.v ^= 1; return r; }
};
istream& operator>>(istream& in, Var& a) {
	in >> a.v;
	a.v = 2*a.v - 2;
	return in;
}
void addImpl(Var u, Var v) {
	adj[u.v][0].emplace_back(v.v);
	adj[v.v][1].emplace_back(u.v);
}

void addClause(Var v1, Var v2) {
	addImpl(!v1, v2);
	addImpl(!v2, v1);
}

bool solvable(ll varcnt) {
	kosaraju(2*varcnt);
	for (ll i = 0; i < varcnt; i++)
		if (comp[2*i] == comp[2*i+1])
			return false;
	return true;
}

Var intToVar(int day, int i){
	if(i > 0) return Var(prefix[day] + i - 1);
	else return Var(prefix[7] + prefix[day] - i - 1);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	ll n; cin >> n;

	prefix[0] = 0;
	for(int i = 0; i < 7; i++){
		cin >> ngames[i];
		prefix[i + 1] = prefix[i] + ngames[i];
	}

	for(int i = 0; i < 7; i++){
		for(int j = 1; j <= ngames[i]; j++){
			addClause(intToVar(i, j), intToVar(i, -j));
			addClause(!intToVar(i, j), !intToVar(i, -j)); // not really necessary
		}
	}
		
	for (ll k = 0; k < n; k++) {
		vector<ll> b(7);
		for(int i=0; i<7; i++) cin >> b[i];
		for (ll i = 0; i < 7; i++)
			for (ll j = 0; j < i; j++)
				addClause(!intToVar(i, b[i]), !intToVar(j, b[j]));
	}
	ll a, b;
	cin >> a >> b;

	// if there is a solution, there is one where Pascal's bets must both be correct.
	//   assume w.l.o.g. that a=1, b=0 and all bets of his friends are false.
	//   Note that there are no two friends who chose opposing teams.
	//   Furthermore, the opponent of b has not been chosen by any friend.
	//   Also note that a and b are not opponents
	//   Hence, if we set b=1, the score of each friend increases by at most 1
	//   and Pascal still wins
	addImpl(!intToVar(5, a), intToVar(5, a));
	addImpl(!intToVar(6, b), intToVar(6, b));

	cout << ("impossible" + 2*solvable(2*prefix[7])) << endl;

	return 0;
}
