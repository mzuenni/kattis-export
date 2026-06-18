#include <bits/stdc++.h>
#include <cassert>
using namespace std;
pair<int,int> f(int r, int c) {
    cout << r << ' ' << c << endl;
    int x, y;
    cin >> x >> y;
    assert(!x == !y);
    if (!x) exit(0);
    assert(1 <= x && x <= 59 && 1 <= y && y <= 42);
    return {x, y};
}
int main() {
    cin.tie(0)->sync_with_stdio(0);
    if (auto [x, y] = f(7, 7); x==7)
        f(f(6, 7).first == 5 ? 8 : 5, 7);
    else
        f(7, f(7, 6).second == 5 ? 8 : 5);
    assert(0);
}
