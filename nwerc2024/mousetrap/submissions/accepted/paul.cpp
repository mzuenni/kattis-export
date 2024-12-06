#include <complex>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;
using C = complex<__int128>;

__int128 cross(C a, C b) {
    return imag(conj(a) * b);
}

int main() {
    int n; cin >> n;
    vector<C> a(n);
    for (auto &z: a) {
        int x, y;
        cin >> x >> y;
        z = C(x, y);
    }

    vector<C> s(n+1);
    for (int i = 0; i < n; i++) {
        s[i+1] = s[i] + a[i];
    }

    __int128 sum = 0, area = 0;
    for (int j = 0; j < n; j++) {
        sum += cross(__int128(j)*a[j] - s[j], s[n]-s[j+1] - __int128(n-1-j)*a[j]);
        area += cross(a[j], a[(j+1)%n]);
    }
    double res = double(sum) / double(area);
    cout << setprecision(15) << res << '\n';
}
