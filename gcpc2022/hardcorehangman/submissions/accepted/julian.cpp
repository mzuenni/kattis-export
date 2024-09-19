#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<char> result(10001, 0);
    for (int i = 0; i < 6; ++i) {
        cout << "? ";
        for (char c = 'a'; c <= 'z'; ++c) {
            if (c & (1 << i)) cout << c;
        }
        cout << "\n";

        int n;
        cin >> n;
        for (int j = 0; j < n; ++j) {
            int t;
            cin >> t;
            result[t - 1] += 1 << i;
        }
    }

    cout << "! ";
    for (char c: result) {
        if (c) cout << static_cast<char>(c + (1 << 6));
        else break;
    }
    cout << endl;
}
