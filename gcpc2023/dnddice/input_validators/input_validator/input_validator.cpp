#include "validation.h"

int main(int argc, char** argv) {
    InputValidator v(argc, argv);
    auto a = v.read_integers("a", 5, 0, 10);
    v.check(*max_element(begin(a), end(a)) > 0, "must have at least one die");
}
