#include <bits/stdc++.h>
#include <cassert>
using namespace std;
bool flipped = false;
pair<int,int> f(int r, int c) {
    if (flipped) swap(r, c);
    cout << r << ' ' << c << endl;
    int x, y;
    cin >> x >> y;
    assert(!x == !y);
    if (!x) exit(0);
    assert(1 <= x && x <= 59 && 1 <= y && y <= 42);
    if (flipped) swap(x, y);
    return {x, y};
}
void threaten(int r, int c, int tr, int tc) {
    if (f(r, c) != pair(tr, tc))
        f(tr, tc);
}
int main() {
    cin.tie(0)->sync_with_stdio(0);
    auto [x, y] = f(7, 7);
    flipped = x == 7;
    int dir = (flipped ? y : x) < 7 ? 1 : -1;
    threaten(7 + 2 * dir, 7, 7 + dir, 7);
    threaten(7 + dir, 8, 7 + 2 * dir, 9);
    f(7 + 3 * dir, 6);
    assert(0);
}
