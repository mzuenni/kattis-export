#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, q;
    cin >> n >> q;
    vector<bool> broken(2 * n + 2);

    while (q--) {
        char c;
        cin >> c;
        if (c == '?') {
            int a, b;
            cin >> a >> b;
            if (a > b) swap(a, b);
            bool possible1 = true, possible2 = true;
            for (int i = a; possible1 && i <= b; ++i) {
                if (broken[i]) possible1 = false;
            }
            for (int i = b; possible2 && i <= a + n; ++i) {
                if (broken[i]) possible2 = false;
            }
            if (possible1 || possible2) {
                cout << "possible\n";
            } else {
                cout << "impossible\n";
            }
        } else {
            int a;
            cin >> a;
            if (c == '-') {
                broken[a] = true;
                broken[a + n] = true;
            } else {
                broken[a] = false;
                broken[a + n] = false;
            }
        }
    }
}
