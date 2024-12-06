#include "validation.h"

// One integer n, the number of surnames.
// n strings s, the surnames.

int main(int argc, char *argv[]) {
    InputValidator v(argc, argv);
    int n = v.read_integer("n", 1, 1'000);
    v.newline();
    std::set<std::string> remainders;
    for (int i = 0; i < n; i++) {
        auto surname = v.read_line("surname", 1, 50, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz '");
        int j = 0;
        while (j < surname.size() && !('A' <= surname[j] && surname[j] <= 'Z'))
            j++;
        v.check(j < surname.size(), "Surname ", surname, " does not contain capital letter!");
        v.check(surname.front()!=' ', "Surname ", surname, " starts with a space!");
        v.check(surname.back()!=' ', "Surname ", surname, " ends with a space!");
        v.check(surname.find("  ")==std::string::npos, "Surname ", surname, " contains consecutive spaces!");
        remainders.insert(surname.substr(j));
    }
    v.check(remainders.size() == n, "Surname remainders are not unique!");
}
