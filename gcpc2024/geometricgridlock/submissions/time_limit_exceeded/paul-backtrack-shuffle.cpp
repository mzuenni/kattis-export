#include <bits/stdc++.h>
using namespace std;

map<char,vector<pair<int,int>>> pentominoes = {
    {'F', {{0,1}, {0,2}, {1,0}, {1,1}, {2,1}}},
    {'I', {{0,0}, {0,1}, {0,2}, {0,3}, {0,4}}},
    {'L', {{0,0}, {0,1}, {0,2}, {0,3}, {1,0}}},
    {'N', {{0,0}, {0,1}, {0,2}, {1,2}, {1,3}}},
    {'P', {{0,0}, {0,1}, {0,2}, {1,0}, {1,1}}},
    {'T', {{0,0}, {0,1}, {0,2}, {1,1}, {2,1}}},
    {'U', {{0,0}, {0,1}, {0,2}, {1,0}, {1,2}}},
    {'V', {{0,0}, {0,1}, {0,2}, {1,0}, {2,0}}},
    {'W', {{0,0}, {0,1}, {1,1}, {1,2}, {2,2}}},
    {'X', {{0,1}, {1,0}, {1,1}, {1,2}, {2,1}}},
    {'Y', {{0,0}, {0,1}, {0,2}, {0,3}, {1,2}}},
    {'Z', {{0,0}, {0,1}, {1,1}, {2,1}, {2,2}}}
};

void normalize(vector<pair<int,int>> &v) {
    sort(begin(v), end(v));
    auto [x0, y0] = v[0];
    for (auto &[x, y]: v) {
        x -= x0, y -= y0;
    }
}

const vector<pair<int,int>> dirs = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};

int main() {
    int h, w;
    cin >> h >> w;

    vector<vector<int>> mark(h, vector<int>(w, -1));
    vector<string> grid(h, string(w, '.'));

    auto check = [&](int i, int j) {
        return 0 <= i && i < h && 0 <= j && j < w && grid[i][j] == '.';
    };

    srand(987);
    auto rec = [&](const auto &self, int i, int j, int k) -> void {
        while (i < h && j < w && grid[i][j] != '.') {
            if (++j == w) i++, j = 0;
        }
        if (i == h) {
            cout << "yes" << '\n';
            for (string s: grid) cout << s << '\n';
            exit(0);
        }

        string s = "FILNPTUVWXYZ";
        random_shuffle(begin(s), end(s));
        for (char c: s) {
            auto p = pentominoes[c];
            for (int rot = 0; rot < 4; rot++) {
                for (int mir = 0; mir < 2; mir++) {
                    normalize(p);

                    bool ok = true;
                    for (auto [di, dj]: p) if (!check(i+di, j+dj)) ok = false;
                    if (ok) {
                        for (auto [di, dj]: p) {
                            mark[i+di][j+dj] = k;
                            grid[i+di][j+dj] = c;
                        }

                        for (auto [di, dj]: p) {
                            for (auto [di2, dj2]: dirs) {
                                int ni = i+di+di2, nj = j+dj+dj2;
                                if (ni < 0 || ni >= h || nj < 0 || nj >= w) continue;
                                if (mark[ni][nj] == k) continue;
                                if (grid[ni][nj] == c) ok = false;
                            }
                        }

                        if (ok) self(self, i, j, k+1);

                        for (auto [di, dj]: p) {
                            mark[i+di][j+dj] = -1;
                            grid[i+di][j+dj] = '.';
                        }
                    }

                    for (auto &[di, dj]: p) swap(di, dj);
                }

                for (auto &[di, dj]: p) di = -di, swap(di, dj);
            }
        }
    };

    if (h*w % 5 == 0) rec(rec, 0, 0, 0);
    cout << "no" << '\n';
}
