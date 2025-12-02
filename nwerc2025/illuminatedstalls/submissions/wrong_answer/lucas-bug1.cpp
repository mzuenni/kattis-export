#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 1e9 + 100;

int n;

bool solve(vector<tuple<int, int, int, int>> segs){
	multiset<int> lengths;
	map<int, set<pair<int, int>>> hori, vert;
	vector<tuple<int, int, int, int>> events;
	for(auto [x1, y1, x2, y2] : segs){
		if(x1 > x2) swap(x1, x2);
		if(y1 > y2) swap(y1, y2);
		if(y1 == y2){
			hori[y1].emplace(x1, x2);
			events.emplace_back(y1, 2, x1, x2);
		}
		else{
			vert[x1].emplace(y1, y2);
			events.emplace_back(y2, 0, x1, -1);
			events.emplace_back(y1, 1, x1, -1);
		}
		lengths.insert(x2-x1 + y2-y1);
	}
	auto check = [&](int y, int x1, int x2) -> bool {
		int sl = x2-x1;
		int ovl = 0, lenl = 0, ovr = 0, lenr = 0;
		{
			auto it = hori[y+sl].lower_bound({x2+1, -inf});
			if(it != hori[y+sl].begin()){
				it--;
				if(it->first <= x2 && x2 <= it->second){
					ovr = x2 - it->first;
					lenr = it->second - it->first;
				}
			}
			it = hori[y+sl].upper_bound({x1, -inf}); // BUG!
			if(it != hori[y+sl].begin()){
				it--;
				if(it->first <= x1 && x1 <= it->second){
					ovl = it->second - x1;
					lenl = it->second - it->first;
				}
			}
		}
		// cerr << ovl << " " << lenl << " " << ovr << " " << lenr << "\n";
		if(ovl + lenr >= sl) return true;
		if(ovr + lenl >= sl) return true;
		vector<int> remLens;
		if(ovl > 0) remLens.push_back(lenl);
		if(ovr > 0) remLens.push_back(lenr);
		{
			auto it = prev(vert[x1].lower_bound({y+1, 0}));
			remLens.push_back(it->second - it->first);
			it = prev(vert[x2].lower_bound({y+1, 0}));
			remLens.push_back(it->second - it->first);
			it = prev(hori[y].lower_bound({x1+1, 0}));
			remLens.push_back(it->second - it->first);
		}
		for(int len : remLens) lengths.erase(lengths.find(len));
		bool res = !lengths.empty() && *lengths.rbegin() >= sl - ovl - ovr;
		for(int len : remLens) lengths.insert(len);
		return res;
	};
	sort(events.rbegin(), events.rend());
	map<int, int> h;
	int cnt = 0;
	for(auto [y, t, x1, x2] : events){
		if(t == 0) h[x1] = y;
		if(t == 1) h.erase(x1);
		if(t == 2){
			vector<pair<int, int>> byH;
			for(auto it = h.lower_bound(x1); it != h.end() && it->first <= x2; it++){
				cnt++;
				if(cnt >= 3*n) return true;
				byH.emplace_back(it->second, it->first);
			}
			sort(byH.rbegin(), byH.rend());
			set<int> s;
			for(auto [ma, x] : byH){
				auto it = s.lower_bound(x);
				if(it != s.end() && ma - y >= *it - x){
					if(check(y, x, *it)) return true;
				}
				if(it != s.begin()){
					it--;
					if(ma - y >= x - *it){
						if(check(y, *it, x)) return true;
					}
				}
				s.insert(x);
			}
		}
	}
	return false;
}

int main(){
	cin.tie(0)->sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        vector<tuple<int, int, int, int>> segs;
        bool ans = false;
        for(int i = 0; i < n; i++){
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            segs.emplace_back(x1, y1, x2, y2);
        }
        for(int r = 0; r < 4; r++){
            ans = ans || solve(segs);
            for(auto &[x1, y1, x2, y2] : segs){
                tie(x1, y1) = pair(-y1, x1);
                tie(x2, y2) = pair(-y2, x2);
            }
        }
        cout << (ans ? "yes\n" : "no\n");
    }
}
