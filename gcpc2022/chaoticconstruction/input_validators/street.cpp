#include <iostream>
#include <set>

using namespace std;
typedef long long ll;

void testRange(ll x, string_view name, ll lo, ll hi) {
	if (x < lo || x > hi) {
		cerr << name << " is not in range: " << x << endl;
		exit(1);
	}
}

constexpr ll MAXN = 100000;
constexpr ll MAXQ = 100000;

int main()
{
    ll n, q;
    cin >> n >> q;
	testRange(n, "n", 2, MAXN);
	testRange(q, "q", 1, MAXQ);
    set<ll> closed;

    while (q--) {
        char c;
        ll a, b;
        cin >> c >> a;
		testRange(a, "a", 1, n);
        if (c == '?') {
			cin >> b;
			testRange(b, "b", 1, n);
		} else {
			if (c != '+' && c != '-') {
				cerr << "Unknown command: \"" << c << "\"" << endl;
				return 1;
			}
            if (closed.count(a) != (c == '+')) {
                cerr << "Tried to close a closed street or open an opened street.\n";
                return 1;
            }
            if (c == '+') closed.erase(a);
            else closed.insert(a);
        }
    }
    return 42;
}
