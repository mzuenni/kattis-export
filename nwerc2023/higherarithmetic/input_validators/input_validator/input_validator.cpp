#include "validation.h"

int main(int argc, char* argv[]) {
	InputValidator v(argc, argv);
	int n = v.read_integer("n", 1, 100000);
	v.newline();

	v.read_integers("a", n, 1, 1e6);
}
