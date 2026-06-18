#include <bits/stdc++.h>
#include <cassert>
using namespace std;
using ll = int64_t;
#define all(x) ::begin(x), ::end(x)
void _d(auto... x) { ((cerr << ' ' << x), ...) << endl; }
#define debug(x...) cerr << "["#x"]:", _d(x)

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int x;
    cin >> x;

    vector<string> a(100, string(100, '.'));
    int h = 1;
    while (h*90 < x + 90) h++;
    h += 2;

    for (int i=0; i<99; i+=3) {
        a[0][i] = a[0][i+1] = a[1][i+1] = a[1][i+2] = '#';
        a[1][i] = a[0][i+2] = 'O';
    }
    for (int i=2; i<98; i+=3) {
        a[i][0] = a[i+1][0] = a[i+1][1] = a[i+2][1] = '#';
        a[i][1] = a[i+2][0] = 'O';

        a[i][92] = a[i+1][92] = a[i+1][93] = a[i+2][93] = '#';
        a[i][93] = a[i+2][92] = 'O';
    }

    for (int i=2; i<92; i+=3) {
        a[h][i] = a[h][i+1] = a[h+1][i+1] = a[h+1][i+2] = '#';
        a[h+1][i] = a[h][i+2] = 'O';
    }

    auto p4 = [&](int x, int y) {
        a[x+1][y] = 'O';
        a[x+1][y-1] = a[x][y] = '#';
    };

    auto p3 = [&](int x, int y) {
        a[x][y-1] = 'O';
        a[x][y] = a[x+1][y-1] = '#';
    };

    h -= 2;
    if (h == 2) {
        if (x % 2 == 0) p4(2, 91 - x/2);
        else p3(2, 91 - x/2);
    } else {
        x = h*90 - x;
        int rem = 45;
        for (int i=2; i<92 && x; i+=2) {
            if (x % 3 == 0 && x/3 <= rem) {
                p3(2, i+1);
                x -= 3;
            } else {
                p4(2, i+1);
                x -= 4;
            }
            rem--;
        }
        assert(x == 0);
    }

    cout << a.size() << " " << a[0].size() << "\n";
    for (string& s : a) cout << s << '\n';
}
