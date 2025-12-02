#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()

int main(){
	cin.tie(0)->sync_with_stdio(false);
	int n, k, q;
	cin >> n >> k >> q;
	vector<vector<tuple<int, int, int>>> byPerson(n);
	vector<tuple<int, int, int>> events;
	for(int i = 0; i < q; i++){
		int a, b, c;
		cin >> a >> b >> c;
		a--;
		byPerson[a].emplace_back(b, c, i);
		events.emplace_back(b, -1, i);
		events.emplace_back(c, 1, i);
	}
	set<pair<int, int>> atHome;
	auto add = [&](int l, int r){
		atHome.emplace(l, r);
	};
	auto check = [&](int i){
		auto it = atHome.lower_bound({i+1, -1});
		int dist = 0;
		while(it != atHome.begin() && dist < 100){
			it = prev(it);
			dist++;
			if(it->second >= i) return true;
		}
		return prev(atHome.lower_bound({i, -1}))->second >= i;
	};
	for(int i = 0; i < n; i++){
		int last = 0;
		sort(all(byPerson[i]));
		for(auto [a, b, ind] : byPerson[i]){
			add(last, a);
			last = b+1;
		}
		add(last, (int)1e9);
	}
	vector<int> s(q);
	for(int i = 0; i < n; i++){
		for(auto [a, b, ind] : byPerson[i]){
			s[ind] = !check(b);
		}
	}

	sort(all(events));
	for(auto [p, t, ind] : events){
		k += t*s[ind];
		if(k < 0){
			cout << "impossible\n";
			return 0;
		}
	}
	for(int x : s) cout << x;
	cout << "\n";
}