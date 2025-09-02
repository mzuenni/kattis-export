#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for (int i = (a); i < (b); i++)

bool do_shuffle;
random_device rd;
mt19937 gen(rd());

int m, n;
vector<pair<int,int>> edges;

vector<int> random_permutation(int n) {
	vector<int> p(n);
	iota(begin(p),end(p),1);
	if (do_shuffle) shuffle(begin(p),end(p),gen);
	return p;
}

void stray_edges() {
	int a, b, density;
	cin >> a >> b >> density;
	
	m = a+b, n = a+b+b;
	
	uniform_int_distribution<int> dis(0,99);

	FOR(i,0,a+b) FOR(j,0,a) if (dis(gen) < density) edges.emplace_back(i,j);
	FOR(i,a,a+b) edges.emplace_back(i,i);
	FOR(i,a,a+b) edges.emplace_back(i,i+b);
}

void hk_worst() {
	int a;
	cin >> a;

	m = n = a*(a+1)/2;

	int k = 0;
	FOR(i,1,a+1) {
		FOR(j,1,i) edges.emplace_back(k+j-1,k+j);
		FOR(d,2,i) FOR(j,d,i) edges.emplace_back(k+j-d,k+j);
		FOR(j,0,i) edges.emplace_back(k+j,k+j);
		k += i;
	}
}

void upward_edges() {
	int a, b;
	cin >> a >> b;
	
	m = n = a;

	set<pair<int,int>> edges_set;
	uniform_int_distribution<int> dis(0,n-1);
	
	while (edges_set.size() < b) {
		int i = dis(gen), j = dis(gen);
		if (i < j) swap(i,j);
		edges_set.emplace(i,j);
	}
	edges.insert(end(edges),begin(edges_set),end(edges_set));
}

int main() {
	string type;
	cin >> type;

	if (type[0] == 's') stray_edges();
	else if (type[0] == 'h') hk_worst();
	else if (type[0] == 'u') upward_edges();
	else assert(0);
	
	cin >> do_shuffle;

	if (do_shuffle) shuffle(begin(edges),end(edges),gen);

	auto p = random_permutation(m);
	auto q = random_permutation(n);
	
	cout << m << " " << n << " " << edges.size() << endl;
	for (auto e: edges) cout << p[e.first] << " " << q[e.second] << endl;
}
