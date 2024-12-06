#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
using i64 = long long;

const double TIMELIMIT = 2;

void compress(vector<int> &i2x, map<int,int> &x2i) {
    sort(begin(i2x), end(i2x));
    i2x.erase(unique(begin(i2x), end(i2x)), end(i2x));
    for (int i = 0; i < int(i2x.size()); i++) {
        x2i[i2x[i]] = i;
    }
}

int main() {
    vector<pair<int,int>> ps(5);
    vector<int> i2x, j2y;
    for (auto &[x, y]: ps) {
        cin >> x >> y;
        i2x.push_back(x);
        j2y.push_back(y);
    }

    map<int,int> x2i, y2j;
    compress(i2x, x2i);
    compress(j2y, y2j);

    int m = i2x.size(), n = j2y.size();
    auto id = [&](int i, int j) { return i*n + j; };

    vector<int> ids;
    for (auto &[x, y]: ps) {
        ids.push_back(id(x2i[x], y2j[y]));
    }

    int best = 1e9;

    auto check = [&](vector<tuple<int,int,int>> rem_edges) {
        vector dist(m*n, vector<int>(m*n, 1e9));
        for (int i = 0; i < m*n; i++) {
            dist[i][i] = 0;
        }

        int sum = 0;
        for (auto [a, b, len]: rem_edges) {
            dist[a][b] = dist[b][a] = len;
            sum += len;
        }
        if (sum >= best) return true;

        for (int k = 0; k < m*n; k++) {
            for (int i = 0; i < m*n; i++) {
                for (int j = 0; j < m*n; j++) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < i; j++) {
                auto [xi, yi] = ps[i];
                auto [xj, yj] = ps[j];
                int need = abs(xj-xi) + abs(yj-yi);
                int have = dist[ids[i]][ids[j]];
                if (need != have) return false;
            }
        }
        best = sum;
        return true;
    };

    vector<tuple<int,int,int>> edges;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i+1 < m) edges.emplace_back(id(i, j), id(i+1, j), i2x[i+1]-i2x[i]);
            if (j+1 < n) edges.emplace_back(id(i, j), id(i, j+1), j2y[j+1]-j2y[j]);
        }
    }
    srand(987);

    clock_t start = clock();

    while (double(clock() - start) / CLOCKS_PER_SEC < 0.9 * TIMELIMIT) {
        random_shuffle(begin(edges), end(edges));

        auto rem_edges = edges;
        for (int k = int(edges.size()) - 1; k >= 0; k--) {
            auto new_rem_edges = rem_edges;
            swap(new_rem_edges[k], new_rem_edges.back());
            new_rem_edges.pop_back();
            if (check(new_rem_edges)) {
                rem_edges = new_rem_edges;
            }
        }
    }
    cout << best << '\n';
}
