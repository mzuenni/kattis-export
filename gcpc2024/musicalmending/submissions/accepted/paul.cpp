#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] -= i;
    }
    nth_element(begin(a), begin(a)+n/2, end(a));
    
    long long res = 0;
    for (int i = 0; i < n; i++) {
        res += abs(a[i]-a[n/2]);
    }
    cout << res << '\n';
}
