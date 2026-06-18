#include "validation.h"

// Check the grammar of the input files.
// You should also check properties of the input.
// E.g., check that a graph is connected.

const long long MAXN = 100'000;
const long long MAX_TOTAL = 1'000'000;
const std::string ASCII_LOWERCASE = "abcdefghijklmnopqrstuvwxyz";

int main(int argc, char *argv[]) {
    InputValidator v(argc, argv);
    int n = v.read_integer("n", 1, MAXN);
    v.newline();
    int total_length = 0;
    for(int i=0; i<n; ++i) {
        auto kind = v.test_strings({"pickup", "dropoff"}, "task type");
        v.space();
        auto item = v.read_string("ai", 1, 20, ASCII_LOWERCASE);
        v.newline();
        total_length += item.size();
    }
    v.check(total_length <= MAX_TOTAL, "total length of all items");
    return 0;
}
