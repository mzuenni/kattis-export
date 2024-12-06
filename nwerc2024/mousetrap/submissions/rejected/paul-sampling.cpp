// @EXPECTED_RESULTS@: TIME_LIMIT_EXCEEDED, WRONG_ANSWER
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>
using namespace std;
using i64 = long long;

const int TIMELIMIT = 3;

int main() {
    int n; cin >> n;
    vector<i64> x(n), y(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }
    x.push_back(x[0]);
    y.push_back(y[0]);

    i64 area = 0;
    for (int i = 0; i < n; i++) {
        area += x[i]*y[i+1] - x[i+1]*y[i];
    }
    area = abs(area);

    mt19937 gen(987);
    uniform_int_distribution<int> dis(0, n-1);

    clock_t start = clock();
    __int128 num = 0, denom = 0;
    while (double(clock() - start) / CLOCKS_PER_SEC < 0.9 * TIMELIMIT) {
        int i = dis(gen);
        int j = dis(gen);
        while (j == i) j = dis(gen);
        int k = dis(gen);
        while (k == i || k == j) k = dis(gen);

        i64 tri = (x[j]-x[i]) * (y[k]-y[i]) - (x[k]-x[i]) * (y[j]-y[i]);
        num += abs(tri), denom += area;
    }

    double res = double(num) / denom;
    res *= double(n) * (n-1) * (n-2) / 6.0;
    cout << fixed << setprecision(20) << res << '\n';
}
