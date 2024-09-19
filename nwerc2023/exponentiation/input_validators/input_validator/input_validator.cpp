#include "validation.h"

int main(int argc, char *argv[]) {
    InputValidator v(argc, argv);
    int n = v.read_integer("n", 2, 1000);
	v.space();
	int m = v.read_integer("m", 1, 1000);
    v.newline();

	for(int i = 0; i < m; i++){
		std::string c = v.read_string("c", 1, 1, "?!");
		v.space();
		int a = v.read_integer("a", 1, n);
		v.space();
		int b = v.read_integer("b", 1, n);
		v.newline();
		v.check(a != b, "equal registers");
	}
}
