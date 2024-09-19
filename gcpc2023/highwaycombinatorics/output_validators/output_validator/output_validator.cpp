#include "validate.h"

constexpr Integer mod = 1000000007;
constexpr Integer lim = 200;

// checks if the lanes were created by placing cars
bool placedCars(std::string a, std::string b) {
	a.push_back('.');
	b.push_back('.');
	for (Integer i = 0; i + 1 < a.size(); i++) {
		if (a[i] == '.' && b[i] == '.') {
			//nothing todo here
		} else if (a[i] == '#' && b[i] == '#') {
			a[i] = '.';
			b[i] = '.';
		} else if (a[i] == '#' && a[i + 1] == '#') {
			a[i] = '.';
			a[i + 1] = '.';
		} else if (b[i] == '#' && b[i + 1] == '#') {
			b[i] = '.';
			b[i + 1] = '.';
		} else {
			// we found
			// ...#.??
			// ....???
			// this is impossible!
			return false;
		}
	}
	return true;
}

// place all cars which are determined uniquely
// due to parity on the left
// #....#???  =>  #....#???
// #......??      #....##??
void placeUnique(std::string& a, std::string& b) {
	for (Integer i = 0; i + 1 < a.size(); i++) {
		if (a[i] == '#' &&
			b[i] == '.' && b[i + 1] == '.') {
			b[i] = '#';
			b[i + 1] = '#';
		}
		if (b[i] == '#' &&
			a[i] == '.' && a[i + 1] == '.') {
			a[i] = '#';
			a[i + 1] = '#';
		}
	}
}

int main(int argc, char *argv[]) {
	OutputValidator::init(argc, argv);
	using namespace OutputValidator;

	Integer x = testIn.integer();

	std::string a = teamAns.string(std::regex("[.#]*"), 1, lim + 1);
	teamAns.newline();
	std::string b = teamAns.string(std::regex("[.#]*"), a.size(), a.size() + 1);
	teamAns.newline();
	teamAns.eof();

	if (!placedCars(a, b)) juryOut << "participants output not generated by placing cars." << WA;
	placeUnique(a, b);

	Integer res;
	if (a != b) {
		res = 0;
	} else {
		std::vector<Integer> fibs = {1, 1};
		for (Integer i = 0; i <= lim; i++) fibs.push_back((fibs[i] + fibs[i + 1]) % mod);

		std::vector<Integer> free = {0};
		for (char c : a) {
			if (c == '.') free.back()++;
			else free.push_back(0);
		}

		res = 1;
		for (Integer x : free) {
			res *= fibs[x];
			res %= mod;
		}
	}

	if (res != x) juryOut << "WA expected: " << x << " found: " << res << WA;
	juryOut << "res=" << res << AC;
}
