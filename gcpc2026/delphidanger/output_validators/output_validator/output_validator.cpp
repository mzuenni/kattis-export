#include "validate.h"
#include "constraints.h"
using namespace OutputValidator;
using namespace std;

int read_input(auto& in, Verdict fail) {
    regex options = regex("(im)?possible");
    string poss = in.string(options);
    in.newline();
    Integer ans = -1;
    if (stringEqual(poss, "possible")) {
        ans = in.integer(1, 1e9);
        in.newline();
    }
    in.eof();
    return ans;
}

int main(int argc, char *argv[]) {
    init(argc, argv);
    int jury_m = read_input(juryAns, FAIL);
    int team_m = read_input(teamAns, WA);

    if (team_m != jury_m) {
        juryOut << "Wrong Answer" << WA;
    } else {
        juryOut << "Ok" << AC;
    }
}
