#include <iostream>
using namespace std;

int main() {
	int n;
	cin >> n;

	std::string pw("aaaaaaaaaA0!");

	while (n--) {
		constexpr int MIN_ASCII = 33;
		constexpr int MAX_ASCII = 126;
		constexpr int NUM_ALPH = MAX_ASCII - MIN_ASCII;
		int k = n;
		
		pw[0] = pw[1] = k % NUM_ALPH + MIN_ASCII;
		k /= NUM_ALPH;
		pw[2] = pw[3] = k % NUM_ALPH + MIN_ASCII;
		k /= NUM_ALPH;
		pw[4] = pw[5] = k % NUM_ALPH + MIN_ASCII;
		k /= NUM_ALPH;
		pw[6] = pw[7] = k % NUM_ALPH + MIN_ASCII;

		cout << pw << endl;
	}
}
