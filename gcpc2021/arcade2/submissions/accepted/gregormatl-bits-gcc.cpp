#include <iostream>

int main() {
	long long n; 
	std::cin >> n;
	std::cout << (__builtin_popcountll(n-1) <= 2 ? std::to_string(((n-1) & (n-2)) + 1) : "impossible") << std::endl;
}