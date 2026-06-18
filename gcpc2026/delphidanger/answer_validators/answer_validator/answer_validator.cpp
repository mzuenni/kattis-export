#include "validation.h"
#include "constraints.h"
using namespace std;

void ASSERT(bool cond, string msg) {
    if (!cond) {
        cerr << msg << endl;
        exit(43);
    }
}

int main(int argc, char *argv[]) {
    AnswerValidator v(argc, argv);

    string poss = v.read_string("poss", 8, 10);
    v.newline();
    ASSERT(poss == "possible" || poss == "impossible", "");
    if (poss == "possible") {
        v.read_integer("ans", 0, 1e9);
        v.newline();
    }
}
