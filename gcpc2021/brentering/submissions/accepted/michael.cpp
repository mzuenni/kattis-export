#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

bitset<26> isVowel(0x104111);

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	string s;
	cin >> s;
	//there is always a lowercase vowel
	while(!isVowel[s.back()-'a']) s.pop_back();
	cout << s << "ntry" << endl;
}
