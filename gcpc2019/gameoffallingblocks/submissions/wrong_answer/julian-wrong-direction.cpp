// Greedy solution
// The next piece is always placed so that its highest part is as low as possible

#include <bits/stdc++.h>

using namespace std;

map<char, vector<string>> pieces;
vector<string> field(25, string(15, ' '));

vector<string> rotate(vector<string> p)
{
    vector<string> result(p.front().size());
    for (int j = p.size() - 1; j >= 0; --j) {
        for (int i = 0; i < p.front().size(); ++i) {
            result[i].push_back(p[j][i]);
        }
    }
    return result;
}

int main()
{
    pieces['I'] = {"...."};
    pieces['J'] = {"...", ".  "};
    pieces['L'] = {"...", "  ."};
    pieces['O'] = {"..", ".."};
    pieces['S'] = {".. ", " .."};
    pieces['T'] = {"...", " . "};
    pieces['Z'] = {" ..", ".. "};

    char c;
    while (cin >> c) {
        if (c == 'W') return 0;

        auto p = pieces[c];

        int min_height = 21;
        int best_placement = -1;
        int best_rotation = 0;

        for (int rotation = 0; rotation < 4; ++rotation) {
            for (int pos = 0; pos <= 10 - p.front().size(); ++pos) {
                bool possible = true;
                int height = 20;
                for (; height >= 0; --height) {
                    for (int i = 0; i < p.front().size(); ++i) {
                        for (int j = 0; j < p.size(); ++j) {
                            if (field[height + j][pos + i] == '.' && p[j][i] == '.') {
                                possible = false;
                            }
                        }
                    }
                    if (!possible) break;
                }
                ++height;
                height += p.size();
                if (height < min_height) {
                    min_height = height;
                    best_placement = pos;
                    best_rotation = rotation;
                }
            }

            p = rotate(p);
        }

        p = pieces[c];
        for (int i = 0; i < best_rotation; ++i) p = rotate(p);
        min_height -= p.size();

        cout << best_rotation << " " << best_placement + 1 << endl;

        for (int i = 0; i < p.front().size(); ++i) {
            for (int j = 0; j < p.size(); ++j) {
                if (p[j][i] == '.') {
                    field[min_height + j][best_placement + i] = p[j][i];
                }
            }
        }

        for (auto s: field) cerr << s << endl;
    }
}
