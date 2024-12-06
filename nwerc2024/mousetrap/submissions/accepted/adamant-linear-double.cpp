#include <bits/stdc++.h>

using namespace std;

using ftype = double;
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
    vector<ftype> x(n), y(n), px(n), py(n), pix(n), piy(n);
    vector<point> p(n);
    ftype area = 0;
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
        p[i] = {x[i], y[i]};
        if(i > 0) {
            area += cross(p[i - 1], p[i]);
            px[i] = px[i - 1] + x[i - 1];
            py[i] = py[i - 1] + y[i - 1];
            pix[i] = pix[i - 1] + x[i - 1] * (i - 1);
            piy[i] = piy[i - 1] + y[i - 1] * (i - 1);
        }
    }
    area += cross(p[n - 1], p[0]);
    ftype triangles = 0;
    for(int i = 0; i < n; i++) {
        triangles -= (n - 2 * i) * (x[i] * py[i] - y[i] * px[i]);
        triangles -= 2 * (x[i] * piy[i] - y[i] * pix[i]);
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
