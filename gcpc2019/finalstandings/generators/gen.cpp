#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll seed;
int teams, problems;
double min_strength, max_strength;
double min_difficulty, max_difficulty;
int problems_solved; // number of problems our team has solved;
int min_solved, max_solved, min_unknown, max_unknown;

default_random_engine e;

double get_strength()
{
    return uniform_real_distribution<double>(min_strength, max_strength)(e);
}

double get_difficulty()
{
    return uniform_real_distribution<double>(min_difficulty, max_difficulty)(e);
}

template<typename T>
void print(const vector<T>& v)
{
    for (size_t i = 0; i < v.size() - 1; ++i) cout << v[i] << " ";
    cout << v.back() << endl;
}

void scoreboard_line(int solved, int unknown)
{
    vector<char> v(problems, '-');
    for (int i = 0; i < solved; ++i) v[i] = 'X';
    for (int i = solved; i < solved + unknown; ++i) v[i] = '?';
    random_shuffle(v.begin(), v.end());
    print(v);
}

int main()
{
    cout << setprecision(6) << fixed;
    cin >> seed >> teams >> problems >> min_strength >> max_strength >> min_difficulty >> max_difficulty >> problems_solved >> min_solved >> max_solved >> min_unknown >> max_unknown;
    e.seed(seed);

    vector<double> p(problems);
    for (double& d: p) d = get_difficulty();
    vector<double> t(teams - 1);
    for (double& d: t) d = get_strength();

    cout << teams << " " << problems << endl;
    print(t);
    print(p);

    for (int i = 0; i < teams - 1; ++i) {
        int solved = uniform_int_distribution<int>(min_solved, max_solved)(e);
        int unknown = uniform_int_distribution<int>(min_unknown, min(max_unknown, problems - solved))(e);
        scoreboard_line(solved, unknown);
    }

    scoreboard_line(problems_solved, 0);
}
