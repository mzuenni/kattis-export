#include <bits/stdc++.h>
using namespace std;
using C = complex<double>;

double cross(C a, C b) {
    return imag(conj(a) * b);
}

int main() {
    int n; cin >> n;
    vector<C> a(n);
    for (auto &z: a) {
        double x, y;
        cin >> x >> y;
        z = C(x, y);
    }

    vector<C> s(n+1);
    for (int i = 0; i < n; i++) {
        s[i+1] = s[i] + a[i];
    }

    double res = 0, area = 0;
    for (int j = 0; j < n; j++) {
        res += cross(double(j)*a[j] - s[j], s[n]-s[j+1] - double(n-1-j)*a[j]);
        area += cross(a[j], a[(j+1)%n]);
    }
    res /= area; 
    cout << fixed << setprecision(8) << res << '\n';
}
