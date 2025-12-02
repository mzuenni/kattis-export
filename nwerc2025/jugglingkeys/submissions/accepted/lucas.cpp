#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()

int main(){
	cin.tie(0)->sync_with_stdio(false);
	int n, k, q;
	cin >> n >> k >> q;
	vector<tuple<int, int, int>> events;
	for(int i = 0; i < q; i++){
		int a, b, c;
		cin >> a >> b >> c;
		events.emplace_back(b, -1, i);
		events.emplace_back(c, 1, i);
	}
	sort(all(events));
	vector<int> s(q);
	int cnt = n;
	for(auto [p, t, ind] : events){
		if(cnt == 0) s[ind] = 1;
		cnt += t;
	}
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