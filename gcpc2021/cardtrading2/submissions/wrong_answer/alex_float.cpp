#include <algorithm>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <tuple>
#include <vector>

using ftype = float;

int main() {
	std::size_t n;
	std::cin >> n;
	std::vector<std::tuple<ftype, std::size_t, std::size_t>> orders(n);
	for(std::size_t i = 0; i < n; ++i) {
		ftype p;
		std::size_t b,s;
		std::cin >> p >> b >> s;
		orders[i] = std::tie(p,b,s);
	}
	std::sort(orders.begin(), orders.end());

	for(std::size_t i = 1; i < n; ++i) {
		std::get<2>(orders[i]) += std::get<2>(orders[i - 1]);
	}

	for(std::size_t i = n - 1; i > 0; --i) {
		std::get<1>(orders[i - 1]) += std::get<1>(orders[i]);
	}

	ftype best_p = 0, turn = 0;
	for(std::size_t i = 0; i < n; ++i) {
		ftype my_p, my_turn;
		std::size_t my_b, my_s;
		std::tie(my_p, my_b, my_s) = orders[i];
		my_turn = my_p * std::min(my_b, my_s);
		if(my_turn > turn) {
			turn = my_turn; best_p = my_p;
		}
	}
	if(turn == 0)
		std::cout << "impossible" << std::endl;
	else
		std::cout << std::setprecision(2) << std::fixed << best_p << " " << turn << std::endl;
	return 0;
}
