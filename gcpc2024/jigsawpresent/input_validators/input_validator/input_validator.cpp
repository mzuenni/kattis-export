#include "limits.h"
#include "validation.h"

int main(int argc, char *argv[]) {
	InputValidator v(argc, argv);
	int n = v.read_integer("n", MIN_N, MAX_N);
	v.newline();
	for(int i = 0; i < n; i++) {
		v.read_integer("x", MIN_X, MAX_X);
		v.space();
		v.read_integer("y", MIN_Y, MAX_Y);
		v.newline();
	}
}
