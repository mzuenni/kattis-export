#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, q;
    cin >> n >> q;
    vector<int> broken;

    while (q--) {
        char c;
        cin >> c;
        if (c == '?') {
            int a, b;
            cin >> a >> b;
            if (a > b) swap(a, b);
            bool possible1 = true, possible2 = true;
            for (int i: broken) {
                if (a <= i && i <= b) possible1 = false;
                if (i <= a || b <= i) possible2 = false;
                if (!possible1 && !possible2) break;
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
                broken.push_back(a);
            } else {
                for (int& i: broken) {
                    if (i == a) {
                        swap(i, broken.back());
                        broken.pop_back();
                        break;
                    }
                }
            }
        }
    }
}
