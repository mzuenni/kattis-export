#include "validation.h"

int main(int argc, char* argv[]) {
	InputValidator v(argc, argv);
	v.read_integer("n", 1, 10'000);
	v.newline();
}
