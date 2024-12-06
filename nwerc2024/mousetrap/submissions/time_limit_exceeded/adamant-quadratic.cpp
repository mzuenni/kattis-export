#include <bits/stdc++.h>

using namespace std;

using ftype = long double;
using point = complex<ftype>;

ftype dot(point a, point b) {
    return (conj(a) * b).real();
}
ftype cross(point a, point b) {
    return (conj(a) * b).imag();
}

void solve() {
    int n;
    cin >> n;
    vector<point> p(n);
    ftype area = 0;
    for (int i = 0; i < n; i++) {
        ftype x, y;
        cin >> x >> y;
        p[i] = {x, y};
        if(i > 0) {
            area += cross(p[i - 1], p[i]);
        }
    }
    area += cross(p[n - 1], p[0]);
    ftype triangles = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < i; j++) {
            triangles += (2 * j - 2 * i + n) * cross(p[j], p[i]);
        }
    }
    cout << fixed << setprecision(6) << triangles / area << endl;
}

int main() {
    //freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
