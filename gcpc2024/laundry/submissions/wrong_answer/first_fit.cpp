#include <vector>
#include <iostream>

using namespace std;

#define A 0
#define B 1
#define C 2
#define AB 3
#define BC 4
#define AC 5
#define ABC 6

int main() {

	int t; cin >> t; 
	while(t--) {
		int k; cin >> k;
		int combinations[7];
		for (int i = 0; i < 7; ++i) {
			cin >> combinations[i];
		}

		int a = combinations[A] / k; int ra = combinations[A] % k;
		int b = combinations[B] / k; int rb = combinations[B] % k;
		int c = combinations[C] / k; int rc = combinations[C] % k;

		int ab = combinations[AB];
		int bc = combinations[BC];
		int ac = combinations[AC];
		
		if (ra > 0) {
			// fill AB into A
			int rem = k - ra;
			ra += min(ab, rem);
			int prevab = ab;
			ab = max(0, ab - rem);
			rem = max(0, rem - prevab);

			// fill AC into A
			ra += min(ac, rem);
			ac = max(0, ac - rem);

			a += ra / k;
			ra %= k;
		}

		if (rb > 0) {
			// fill AB into B
			int rem = k - rb;
			rb += min(ab, rem);
			int prevab = ab;
			ab = max(0, ab - rem);
			rem = max(0, rem - prevab);

			// fill BC into B
			rb += min(bc, rem);
			bc = max(0, bc - rem);

			b += rb / k;
			rb %= k;
		}

		if (rc > 0) {
			// fill AC into C
			int rem = k - rc;
			rc += min(ac, rem);
			int prevac = ac;
			ac = max(0, ac - rem);
			rem = max(0, rem - prevac);

			// fill BC into C
			rc += min(bc, rem);
			bc = max(0, bc - rem);

			c += rc / k;
			rc %= k;
		}

		int remaining = 0;
		if (ra > 0)
			remaining += k - ra;
		if (rb > 0)
			remaining += k - rb;
		if (rc > 0)
			remaining += k - rc;

		combinations[ABC] = max(0, combinations[ABC] - remaining);
		if (ra > 0) {++a; ra = 0;}
		if (rb > 0) {++b; rb = 0;}
		if (rc > 0) {++c; rc = 0;}

		if (ab % k != 0) {
			combinations[ABC] -= k - ab%k;
		}
		if (ac % k != 0) {
			combinations[ABC] -= k - ac%k;
		}
		if (bc % k != 0) {
			combinations[ABC] -= k - bc%k;
		}

		combinations[ABC] = max(0, combinations[ABC]);

		cout << a + b + c + ((ab + k - 1) / k + (ac + k - 1) / k + (bc + k - 1) / k + (combinations[ABC] + k - 1) / k) << endl;
	}
}
