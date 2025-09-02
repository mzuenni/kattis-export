#include <bits/stdc++.h>

using namespace std;

string operator*(string a, size_t i)
{
    string result;
    for (size_t j = 0; j < i; ++j) result += a;
    return result;
}

int get_score(const string& s)
{
    for (size_t i = 1; i < s.size(); ++i) {
        if (s.size() % i != 0) continue;
        if (s.substr(0, i) * (s.size() / i) == s) return i;
    }
    return s.size();
}

int main()
{
    int n;
    cin >> n;
    vector<int> score[2];
    for (int x: {0, 1}) {
        score[x].resize(n);
        for (int& s: score[x]) {
            string str;
            cin >> str;
            s = get_score(str);
        }
        sort(score[x].begin(), score[x].end());
    }

    long long result = 0;
    for (int i = 0; i < n; ++i) result += (score[0][i] - score[1][i]) * (score[0][i] - score[1][i]);
    cout << result << endl;
}
