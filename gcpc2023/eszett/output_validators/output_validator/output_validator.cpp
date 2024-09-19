#include "validation.h"
using namespace std;

int main(int argc, char **argv) {
    std::ifstream in(argv[1]);
    OutputValidator v(argc, argv);

    string s; in >> s;
    for (char &c: s) c = tolower(c);

    set<string> a = {s};
    while (true) {
        set<string> b = a;
        for (string t: a) {
            for (auto i = t.find("ss", 0); i != string::npos; i = t.find("ss", i+1)) {
                b.insert(t.substr(0, i) + "b" + t.substr(i+2));
            }
        }
        if (a == b) break;
        a = b;
    }

    set<string> b;
    while (!a.empty()) {
        string t = v.read_string("t", 1, 20);
        for (char &c: t) c = tolower(c);
        v.newline();
        v.check(!b.count(t), "duplicate string");
        v.check(a.count(t), "invalid string");
        a.erase(t);
        b.insert(t);
    }
}
