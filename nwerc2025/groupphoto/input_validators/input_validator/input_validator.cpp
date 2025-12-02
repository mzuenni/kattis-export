#include "validation.h"
using namespace std;
using ll = long long;

constexpr int maxN = 5e5;

int main(int argc, char* argv[]) {
	InputValidator v(argc, argv);
	ll n = v.read_integer("n", 1, maxN);
	v.newline();
	vector<ll> a = v.read_integers("a", n, 1, n, Unique);
	v.eof_and_AC();
	return 0;
}
