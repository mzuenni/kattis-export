#include<bits/stdc++.h>
using namespace std;

int main() {
    double d, s, e;
    cin >> d >> s >> e;
    double x = max(0.0, s - d + s + e);
    cout << setprecision(10) << (1.0 - (s - x) / d) * ((s - x) / (d - s - e)) << endl;
    return 0;
}

