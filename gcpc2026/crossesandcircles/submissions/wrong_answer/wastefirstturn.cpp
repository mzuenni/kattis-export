#include <bits/stdc++.h>
using namespace std;
pair<int,int> f(int r, int c) {
    cout << r << ' ' << c << endl;
    int x, y;
    cin >> x >> y;
    if (!x) exit(0);
    return {x, y};
}
int main() {
    cin.tie(0)->sync_with_stdio(0);
    auto [xx, yy] = f(1, 1);
    int off = xx < 10 && yy < 10;
    if (auto [x, y] = f(7 + off, 7 + off); x==7)
        f(f(6 + off, 7 + off).first == 5 + off ? 8 + off : 5 + off, 7 + off);
    else
        f(7 + off, f(7 + off, 6 + off).second == 5 + off ? 8 + off : 5 + off);
}
