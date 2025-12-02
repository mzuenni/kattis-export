#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()
using ld = long double;

int main(){
	cin.tie(0)->sync_with_stdio(false);
	int n;
	string s;
	cin >> n >> s;
	vector<int> cnt(3);
    string colours = "rgb";
	for(char c : s){
		cnt[colours.find(c)]++;
	}
	sort(all(cnt));
	ld ans = cnt[0] * 1.5;
	ld p = pow(0.5, cnt[0]);
	for(int i = 0; i <= cnt[0]; i++){
		ans += 3 * min(cnt[1]+i, cnt[2]+cnt[0]-i) * p;
		p *= ld(cnt[0]-i) / (i+1);
	}
	cout << setprecision(10) << ans << "\n";
}