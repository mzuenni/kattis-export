#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, c;
    cin >> n >> m >> c;

    vector<int> attendance(n), fav_count(m);
    vector<vector<int>> favs(m), fans(n);
    for (int i = 0; i < m; i++) {
        cin >> fav_count[i];
        favs[i].resize(fav_count[i]);
        for (int &j: favs[i]) {
            cin >> j, j--;
            fans[j].push_back(i);
            attendance[j]++;
        }
    }

    vector<int> invite(n, 1), attend(m, 1);
    queue<pair<int,int>> removals;

    auto consider_for_removal = [&](int i, int is_fan) {
        if (is_fan && 2*fav_count[i] < ssize(favs[i]) && attend[i]) {
            attend[i] = 0;
            removals.emplace(i, 1);
        }
        if (!is_fan && attendance[i] < c && invite[i]) {
            invite[i] = 0;
            removals.emplace(i, 0);
        }
    };

    for (int i = 0; i < n; i++) {
        consider_for_removal(i, 0);
    }

    while (!removals.empty()) {
        auto [i, is_fan] = removals.front();
        removals.pop();
        if (is_fan) {
            for (int j: favs[i]) {
                attendance[j]--;
                consider_for_removal(j, 0);
            }
        } else {
            for (int j: fans[i]) {
                fav_count[j]--;
                consider_for_removal(j, 1);
            }
        }
    }

    int k = accumulate(begin(invite), end(invite), 0);
    if (k > 0) {
        cout << "possible" << '\n';
        cout << k << '\n';
        for (int i = 0; i < n; i++) {
            if (invite[i]) cout << i+1 << " \n"[--k == 0];
        }
    } else {
        cout << "impossible" << '\n';
    }
}
