#include "validation.h"

int main(int argc, char* argv[]) {
	InputValidator v(argc, argv);
	long long max = 1'000'000'000ll * 1'000'000'000 - 1;
	v.read_integer("a", 1, max);
	v.space();
	v.read_integer("b", 1, max);
	v.space();
	v.read_integer("c", 1, max);
	v.space();
	v.read_integer("d", 1, max);
	v.newline();
}
