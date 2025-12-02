// @EXPECTED_RESULTS@: WRONG_ANSWER, RUN_TIME_ERROR
#include <bits/stdc++.h>
#define f(i, s, k, l) for (int i = s; i < k; i += l)
#define for0(i, k) f(i, 0, k, 1)

#define pl pair<long long, long long>
#define pb push_back

#define vl vector<long long>
#define vi vector<int>
#define sz(x) (ll)(x).size()

using namespace std;
using ll = long long;
using ld = long double;

ll h, w;
bool check(vector<vector<char>> mat) {
    ll count = 0;
    for0(y, h) {
        for0(x, w) {
            for (ll dx = -1; dx <= 1; dx++) {
                for (ll dy = -1; dy <= 1; dy++) {
                    if (x + 2 * dx >= w || x + 2 * dx < 0) continue;
                    if (y + 2 * dy >= h || y + 2 * dy < 0) continue;
                    if (mat[y + 0 * dy][x + 0 * dx] != 'f') continue;
                    if (mat[y + 1 * dy][x + 1 * dx] != 'o') continue;
                    if (mat[y + 2 * dy][x + 2 * dx] != 'x') continue;
                    count++;
                }
            }
        }
    }
    return count == 1;
}

vector<vector<char>> fill(vector<vector<char>> mat, string rest) {
    for0(i, h) {
        for0(j, w) {
            if (mat[i][j] != '?') continue;
            mat[i][j] = rest.back();
            rest.pop_back();
        }
    }
    return mat;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
    vl count(3);
    map<char, ll> c;
    c['k'] = 0;
    c['i'] = 0;
    c['t'] = 0;
    cin >> h >> w >> c['k'] >> c['i'] >> c['t'];

    vector<vector<char>> mat(h, vector<char>(w, '?'));
    ll oRow = (h - 1) / 2;
    ll oCol = (w - 1) / 2;

    mat[oRow][oCol - 1] = 'k';
    mat[oRow][oCol] = 'i';
    mat[oRow][oCol + 1] = 't';

    ll outline = min(w, 5ll) * min(h, 3ll) - 3;

    char fill1 = '?';
    char fill2= '?';
    if (c['k'] >= outline + 1) {
        fill1 = 'k';
        fill2 = 'k';
    }
    else if (c['t'] >= outline + 1) {
        fill1 = 't';
        fill2 = 't';
    }
    else if (c['k'] >= outline / 2 + 1 && c['t'] >= outline / 2 + 1) {
        fill1 = 'k';
        fill2 = 't';
    }

    if (oRow >= 1) {
        for (ll i = max(0ll, oCol - 2); i <= min(w - 1, oCol + 2); i++) {
            mat[oRow - 1][i] = (i - oCol + 2) % 2 == 0 ? fill1 : fill2;
            mat[oRow + 1][i] = (i - oCol + 2) % 2 == 0 ? fill1 : fill2;
        }
    }
    if (oCol >= 2) {
            mat[oRow][oCol - 2] = fill2;
            mat[oRow][oCol + 2] = fill2;
    }

    for0(i, h) {
        for0(j, w) {
            if (mat[i][j] != ' ') c[mat[i][j]]--;
        }
    }

    string kit = "kit";
    string rest;
    vector<vector<char>> filled;
    while (next_permutation(kit.begin(), kit.end())) {
        rest = string(c[kit[0]], kit[0]) + string(c[kit[1]], kit[1]) + string(c[kit[2]], kit[2]);
        filled = fill(mat, rest);
        if (check(filled)) break;
    }

    for0(i, h) {
        for0(j, w) cout << filled[i][j];
        cout << endl;
    }
}
