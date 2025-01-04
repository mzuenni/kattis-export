#include "validation.h"

constexpr size_t max_length = 2'000;
constexpr size_t max_tokens = 2'000;
constexpr size_t max_queries = 2'000;

const std::string ok_chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789()";

void read_code(InputValidator& v, const std::string& name) {
    size_t n = v.read_integer(name + "_n", 1, max_tokens);
    v.newline();
    size_t total_length = 0;
    for (size_t i = 0; i < n; i++) {
        if (i > 0) v.space();
        auto s = v.read_string(name + "_token_" + std::to_string(i), 1, max_length - total_length, ok_chars);
        total_length += s.size();
    }
    v.check(total_length <= max_length, name, ": max length exceeded, got ", total_length);
    v.newline();
}

int main(int argc, char *argv[]) {
    InputValidator v(argc, argv);
    read_code(v, "reference");
    size_t q = v.read_integer("q", 1, max_queries);
    v.newline();
    for (size_t i = 0; i < q; i++)
        read_code(v, "query_" + std::to_string(q));
    v.eof_and_AC();
}
