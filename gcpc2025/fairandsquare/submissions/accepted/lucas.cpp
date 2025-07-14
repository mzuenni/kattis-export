#include <bits/stdc++.h>
using namespace std;

int main(){
	int n, m;
	cin >> n >> m;
	vector<string> v(n);
	for(auto& s : v) cin >> s;
	int total = 0;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			total += v[i][j] == '#';
		}
	}
	auto check = [&](int len){
		if(total % (len) != 0) return false;
		vector<vector<bool>> used(n, vector<bool>(m));
		for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++){
				if(used[i][j] || v[i][j] == '.') continue;
				if(i + len > n || j + len > m) return false;
				for(int i2 = i; i2 < i+len; i2++){
					for(int j2 = j; j2 < j+len; j2++){
						if(used[i2][j2] || v[i2][j2] == '.') return false;
						used[i2][j2] = true;
					}
				}
			}
		}
		return true;
	};
	for(int ans = min(n, m); ans >= 1; ans--){
		if(check(ans)){
			cout << ans << "\n";
			return 0;
		}
	}
}