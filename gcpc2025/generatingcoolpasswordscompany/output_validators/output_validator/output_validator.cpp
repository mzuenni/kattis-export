#include "validation.h"
#include <algorithm>
#include <set>
#include <string>
using namespace std;

int edit_distance(string s, string t) {
    int m = s.size(), n = t.size();
    vector<vector<int>> dp(m+1, vector<int>(n+1, 1000));
    dp[0][0] = 0;
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i < m && j < n) {
                dp[i+1][j+1] = min(dp[i+1][j+1], dp[i][j] + (s[i] != t[j]));
            }
            if (i < m) {
                dp[i+1][j] = min(dp[i+1][j], dp[i][j] + 1);
            }
            if (j < n) {
                dp[i][j+1] = min(dp[i][j+1], dp[i][j] + 1);
            }
        }
    }
    return dp[m][n];
}

bool isother(char c) {
    return !islower(c) && !isupper(c) && !isdigit(c);
}

int main(int argc, char *argv[]) {
    std::ifstream in(argv[1]);
    OutputValidator v(argc, argv);

    string allowed_chars;
    for (char c = '!'; c <= '~'; c++) {
        allowed_chars.push_back(c);
    }

    int n; in >> n;

    vector<string> passwords;
    for (int k = 0; k < n; k++) {
        string s = v.read_string("s", 8, 12, allowed_chars);
        v.newline();

        v.check(any_of(s.begin(), s.end(), ::islower),
                "Password ", s, " does not have a lowercase letter.");

        v.check(any_of(s.begin(), s.end(), ::isupper),
                "Password ", s, " does not have an uppercase letter.");

        v.check(any_of(s.begin(), s.end(), ::isdigit),
                "Password ", s, " does not have a digit.");

        v.check(any_of(s.begin(), s.end(), isother),
                "Password ", s, " does not have a special character.");

        for (string t: passwords) {
            int d = edit_distance(s, t);
            v.check(d >= 2, "Passwords ", s, " and ", t, " are too similar (edit distance ", d, ").");
        }
        passwords.push_back(s);
    }
}
