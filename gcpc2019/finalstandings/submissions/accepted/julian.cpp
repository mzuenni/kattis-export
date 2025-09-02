#include <bits/stdc++.h>

using namespace std;

int main()
{
    long double result = 1;

    int t, p;
    cin >> t >> p;
    vector<long double> teams(t - 1), problems(p);
    for (auto& d: teams) cin >> d;
    for (auto& d: problems) cin >> d;

    vector<vector<char>> scoreboard(t - 1, vector<char>(p));
    for (auto& s: scoreboard) {
        for (char& c: s) cin >> c;
    }

    int own_score = 0;
    for (int i = 0; i < p; ++i) {
        char c;
        cin >> c;
        if (c == 'X') ++own_score;
    }

    for (int team = 0; team < t - 1; ++team) {
        auto scores = scoreboard[team];
        auto strength = teams[team];

        vector<long double> dp(p + 1, 0);
        dp[0] = 1;
        for (int problem = 0; problem < p; ++problem) {
            if (scores[problem] == 'X') {
                for (int i = p; i > 0; --i) dp[i] = dp[i - 1];
                dp[0] = 0;
            } else if (scores[problem] == '?') {
                auto prob = strength * problems[problem];
                for (int i = p; i > 0; --i) {
                    dp[i] = dp[i] * (1 - prob) + dp[i - 1] * prob;
                }
                dp[0] *= (1 - prob);
            }
        }

        long double r = 0;
        for (int i = 0; i <= own_score; ++i) r += dp[i];
        result *= r;
    }

    cout << result << endl;
}
