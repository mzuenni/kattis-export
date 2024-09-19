#include "validation.h"

int main(int argc, char** argv) {
    InputValidator v(argc, argv);
    int n = v.read_integer("n", 1, 1000);
    v.newline();

    std::vector<std::string> shapes = {"triangle", "square", "circle"};
    while (n--) {
        v.test_strings(shapes);
        v.space();
        v.read_integer("a", 1, int(1e9));
        v.newline();
    }
}
