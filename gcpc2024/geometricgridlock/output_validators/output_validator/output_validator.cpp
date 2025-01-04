#include "validation.h"
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
    int xmin = 1000, ymin = 1000;
    for (auto [x, y]: v) {
        xmin = min(xmin, x);
        ymin = min(ymin, y);
    }
    for (auto &[x, y]: v) {
        x -= xmin, y -= ymin;
    }
    sort(begin(v), end(v));
}

bool possible(int h, int w) {
    if (h*w % 5 != 0) return false;
    if (h%5 != 0) swap(h, w);
    if (w == 1) return h == 5;
    if (w == 2) return h >= 10;
    return true;
}

int main(int argc, char *argv[]) {
    ifstream in(argv[1]);
    OutputValidator v(argc, argv);

    int h, w;
    in >> h >> w;

    string answer = v.test_strings({"yes", "no"}, "answer");
    v.newline();

    if (!possible(h, w)) {
        v.check(answer == "no",  "Expected 'no', got 'yes'.");
    } else {
        v.check(answer == "yes", "Expected 'yes', got 'no'.");

        vector<string> grid(h);
        for (int i = 0; i < h; i++) {
            grid[i] = v.read_string("s", w, w, "FILNPTUVWXYZ");
            v.newline();
        }

        int C = 0;
        vector<vector<int>> comp(h, vector<int>(w, -1));

        auto dfs = [&](const auto &self, char c, int i, int j, auto &p) {
            if (i < 0 || i >= h || j < 0 || j >= w) return;
            if (comp[i][j] != -1 || grid[i][j] != c) return;
            comp[i][j] = C;
            p.emplace_back(i, j);
            self(self, c, i-1, j, p);
            self(self, c, i+1, j, p);
            self(self, c, i, j-1, p);
            self(self, c, i, j+1, p);
        };

        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                if (comp[i][j] != -1) continue;
                vector<pair<int,int>> p;
                dfs(dfs, grid[i][j], i, j, p);
                C++;

                v.check(size(p) == 5, "Found component of size ", size(p), ".");

                bool ok = false;
                for (int rot = 0; rot < 4; rot++) {
                    for (int mir = 0; mir < 2; mir++) {
                        normalize(p);
                        if (p == pentominoes[grid[i][j]]) ok = true;

                        for (auto &[i, j]: p) swap(i, j);
                    }

                    for (auto &[i, j]: p) i = -i, swap(i, j);
                }

                v.check(ok, "Component labelled incorrectly.");
            }
        }
    }
}
