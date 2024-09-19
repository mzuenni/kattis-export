#include <iostream>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;


ll n, k;
ll todo = 0;
bool hit[100][100];

void shoot(ll x, ll y) {
	if (x < 0 || x >= n) return;
	if (y < 0 || y >= n) return;
	if (hit[y][x]) return;
	hit[y][x] = true;
	cout << x+1 << " " << y+1 << endl;
	string res;
	cin >> res;
	if (res != "miss") {
		todo--;
		if (todo == 0) exit(0);
		shoot(x-1, y);
		shoot(x, y-1);
		shoot(x+1, y);
		shoot(x, y+1);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n >> k;
	todo = 5 * k;

	for (ll y = 0; y < n; y++) {
		for (ll x = 0; x < n; x++) {
			if ((x+y) % 5 == 4) shoot(x, y);
		}
	}
}
