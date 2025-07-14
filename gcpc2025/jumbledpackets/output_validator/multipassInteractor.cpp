#include "validate.h"
using namespace std;

const regex ACTION("Encode|Decode");
const regex BINARY("[01]+");
const regex TERNARY("[012]+");

using namespace OutputValidator;
string team_ternary, original_binary;

vector<Integer> fixed() { // the shifts fixed in the .ans file
    Integer n = juryAns.integer();
    return juryAns.integers(n);
}

vector<Integer> random_shifts() { // random distinct shifts
    Integer n = juryAns.integer();

    unsigned long long seed = 0;
    for (int i=0; i<original_binary.size(); i++) seed += original_binary[i] * (i+1);
    Random::seed(seed);
    return Random::distinct(n, 0, original_binary.size());
}

vector<Integer> first_letter() { // first 3 occurences of each letter
    vector<Integer> shifts;
    for (char c='0'; c<='2'; c++) {
        int cnt = 0;
        for (int j=0; j < team_ternary.size() && cnt<3; j++) {
            if (team_ternary[j] == c) {
                cnt++;
                shifts.push_back(j);
            }
        }
    }
    return shifts;
}

vector<Integer> last_letter() { // last 3 occurences of each letter
    vector<Integer> shifts;
    for (char c='0'; c<='2'; c++) {
        int cnt = 0;
        for (int j = (ll)team_ternary.size()-1; j>=0 && cnt<3; j--) {
            if (team_ternary[j] == c) {
                cnt++;
                shifts.push_back(j);
            }
        }
    }
    return shifts;
}

vector<Integer> first_double() { // first occurence of each two-letter pattern
    vector<Integer> shifts;
    vector<string> patterns = {"00", "01", "02", "10", "11", "12", "20", "21", "22"};
    for (string p : patterns) {
        Integer x = team_ternary.find(p);
        if (x != (Integer)string::npos) shifts.push_back(x);
    }
    return shifts;
}

vector<Integer> last_double() { // last occurence of each two-letter pattern
    vector<Integer> shifts;
    vector<string> patterns = {"00", "01", "02", "10", "11", "12", "20", "21", "22"};
    for (string p : patterns) {
        Integer x = team_ternary.rfind(p);
        if (x != (Integer)string::npos) shifts.push_back(x);
    }
    return shifts;
}

vector<Integer> get_shifts(string mode) {
    if (mode == "fixed") return fixed();
    else if (mode == "random") return random_shifts();
    else if (mode == "first-letter") return first_letter();
    else if (mode == "last-letter") return last_letter();
    else if (mode == "first-double") return first_double();
    else if (mode == "last-double") return last_double();

    juryErr << "Mode " << mode << " unknown" << FAIL;
    return {};
}

int main(int argc, char **argv) {
    OutputValidator::init(argc, argv);
    Multipass::init();
    using namespace Multipass;
    if (!caseSensitive) juryErr << "Call with: case_sensitive" << FAIL;

    string action = testIn.string(ACTION);
    Integer n = testIn.integer();

    auto write_test = [&]() {
        string mode = juryAns.string();
        vector<Integer> shifts = get_shifts(mode);
        
        if (pass >= shifts.size()) juryOut << "OK!" << AC; // no more passes

        string s = team_ternary;
        rotate(s.begin(), s.begin() + shifts[pass], s.end());

        nextstate << original_binary << endl << team_ternary << endl; // remember for next pass

        nextpass << "Decode" << endl; // write next team input file
        nextpass << n << endl;
        nextpass << s << endl;

        NEXT();
    };

    if (pass == 0) {
        if (action != "Encode") {
            juryErr << "Action " << action << " not valid in first pass" << FAIL;
        }
        original_binary = testIn.string();
        team_ternary = teamAns.string(TERNARY, n, n+1);

        write_test();
    } else {
        if (action != "Decode") {
            juryErr << "Action " << action << " not valid in pass " << pass+1 << FAIL;
        }

        original_binary = prevstate.string();
        team_ternary = prevstate.string();
        string team_binary = teamAns.string(BINARY, n, n+1);
        
        if (team_binary != original_binary) {
            juryOut << "Team output " << team_binary << " does not match original string " << original_binary << WA;
        }

        write_test();
    }
}
