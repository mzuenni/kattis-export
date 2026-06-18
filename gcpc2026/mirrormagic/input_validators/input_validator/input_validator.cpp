#include "validation.h"

#define int int64_t

struct pt {
	int x = 0, y = 0;
	auto operator<=>(const pt&) const = default;
};

constexpr int min_coord = -1'000'000;
constexpr int max_coord = 1'000'000;

signed main(signed argc, char* argv[])
{
	InputValidator v(argc, argv);
	int n = v.read_integer("n", 1, 100'000);
	v.newline();

	std::set<pt> alice;
	std::set<pt> bob;

	// pt asum { }, bsum { };
	for (int i = 0, x, y; i < n; i++) {
		x = v.read_integer("alice:x_" + std::to_string(i), min_coord, max_coord);
		v.space();
		y = v.read_integer("alice:y_" + std::to_string(i), min_coord, max_coord);
		v.newline();
		v.check(alice.emplace(x, y).second, i, "th alice's candle ", x, ",", y, " appears before already!");
		// asum.x += x, asum.y += y;
	}
	for (int i = 0, x, y; i < n; i++) {
		x = v.read_integer("bob:x_" + std::to_string(i), min_coord, max_coord);
		v.space();
		y = v.read_integer("bob:y_" + std::to_string(i), min_coord, max_coord);
		v.newline();
		v.check(not alice.count(pt { x, y }), i, "th bob's candle ", x, ",", y, " is at the same position as one of alice's candles!");
		v.check(bob.emplace(x, y).second, i, "th bob's candle ", x, ",", y, " appears before already!");
		// bsum.x += x, bsum.y += y;
	}
	// v.check(asum != bsum, "the two chandeliers have the same COM!");
	return 0;
}
