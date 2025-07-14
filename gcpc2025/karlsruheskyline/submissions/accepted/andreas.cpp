#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, a, b;
    cin >> n >> a >> b;
    if (a + b > n + 1 || a + b < 3) {
        cout << "no" << endl;
        return 0;
    }
    cout << "yes" << endl;
    vector<int> res(n);
    if (b == 1) {
        res[n-1] = n;
        for (int i = 0; i < a-1; i++) res[i] = n - a + i + 1;
        for (int i = a-1, j = 1; i < n-1; i++, j++) res[i] = j;
    } else {
        for (int i = 0; i < a; i++) res[i] = n - (a - i) + 1;
        for (int i = n-b+1, j = 0; i < n; i++, j++) res[i] = (n - a) - j;
        for (int i = a, j = 1; i < n-b+1; i++, j++) res[i] = j;
    }
    
    for (int k: res) cout << k << ' ';
    cout << endl;

    return 0;
}