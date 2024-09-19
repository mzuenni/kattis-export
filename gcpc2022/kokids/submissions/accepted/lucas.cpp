#include <iostream>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    string s;
    cin >> s;

    k -= s[0] == 'R';

    for (int i = 0; i < n - 1; i++) {
        k -= s[i] == s[i + 1];
    }

    cout << max(0, k) << "\n";
}