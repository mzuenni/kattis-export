#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)size(x)
using ll = long long;

struct Fen{
	Fen(int n):fen(n+1){}

	vector<int> fen;
	void add(int i, int x){
		for(i++; i < sz(fen); i += i&-i) fen[i] += x;
	}
	int qry(int i){
		int res = 0;
		for(; i; i -= i&-i) res += fen[i];
		return res;
	}
	int qry(int l, int r){
		return qry(r)-qry(l);
	}
};

int main(){
	int n, b; ll tBus, tExit;
	cin >> n >> b >> tBus >> tExit;
	Fen f1(b), fm(b);
	vector<ll> d(b);
	for(ll &e : d) cin >> e;
    for (int i = 1; i < b; i++) d[i] += d[i-1];
	vector<int> to(n);
	for(int &e : to) cin >> e, e--;
	ll lo = 0, hi = 1e12;
	auto check = [&](ll maxTime){
		vector<bool> isIn(b);
		auto reset = [&](int l, int r){
			for(int i = l; i < r; i++){
				fm.add(to[i], -1);
				if(isIn[to[i]]){
					isIn[to[i]] = false;
					f1.add(to[i], -1);
				}
			}
		};
		int last = 0, i = 0;
		for(int bus = 0; i < n; bus++){
			ll cost = bus*tBus, maxPos = 0;
			while(i < n){
				maxPos = max(maxPos, d[to[i]]);
				if(!isIn[to[i]]){
					cost += (f1.qry(to[i])+fm.qry(to[i], b)+1)*2*tExit;
					f1.add(to[i], 1);
					isIn[to[i]] = true;
				}
				else{
					cost += (f1.qry(to[i])+1)*2*tExit;
				}
				fm.add(to[i], 1);
				if(cost + maxPos > maxTime) break;
				i++;
			}
			reset(last, min(i+1, n));
			if(last == i) return false;
			last = i;
		}
		return true;
	};
	while(lo + 1 < hi){
		ll mid = (lo + hi) / 2;
		if(check(mid)) hi = mid;
		else lo = mid;
	}
	cout << hi << "\n";
}
