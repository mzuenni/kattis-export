#include <bits/stdc++.h>

using namespace std;

size_t n;
vector<vector<pair<char, int>>> m, level;
map<string, int> artifact_id;

void result(string s)
{
    cout << "R " << s << "\n";
    exit(0);
}

int level_dfs()
{
    string artifact, paths;
    cin >> artifact >> paths;
    if (artifact_id.count(artifact)) return artifact_id[artifact];
    size_t id = artifact_id.size();
    artifact_id[artifact] = id;

    if (id >= n) result("no");

    for (char c: paths) {
        cout << "W " << c << endl;
        int end = level_dfs();
        cout << "W " << c << endl;
        string a, p;
        cin >> a >> p;

        level[id].emplace_back(c, end);
    }

    return id;
}

bool compare(int mm, int ll, vector<char>& visited, vector<int>& a)
{
    if (visited[mm]) return a[mm] == ll;
    visited[mm] = true;
    a[mm] = ll;

    if (m[mm].size() != level[ll].size()) return false;

    for (size_t i = 0; i < m[mm].size(); ++i) {
        auto mp = m[mm][i], lp = level[ll][i];
        if (mp.first != lp.first) return false;
        if (!compare(mp.second, lp.second, visited, a)) return false;
    }

    return true;
}

int main()
{
    cin >> n;
    m.resize(n);
    level.resize(n);

    for (auto& v: m) {
        int k;
        cin >> k;
        while (k--) {
            char t;
            int mm;
            cin >> t >> mm;
            --mm;
            v.emplace_back(t, mm);
        }
        sort(v.begin(), v.end());
    }

    int start = level_dfs();
    for (auto& v: level) sort(v.begin(), v.end());

    if (n != artifact_id.size()) result("no");

    int r = -1;
    vector<char> visited;
    vector<int> a;
    for (size_t i = 0; i < n; ++i) {
        visited.assign(n, false);
        a.assign(n, -1);
        if (compare(i, start, visited, a)) {
            cerr << i << endl;
            if (r != -1) result("ambiguous");
            else r = i;
        }
    }

    if (r == -1) result("no");
    else result(to_string(r + 1));
}
