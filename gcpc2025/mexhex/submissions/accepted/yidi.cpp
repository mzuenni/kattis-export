#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, d;
    cin >> n >> d;

    vector<vector<int>> a(n+1);
    for (int i=0; i<n; i++) {
        int x;
        cin >> x;
        a[x].push_back(i);
    }

    for (int x=0; x<=n; x++) {
        int last = 0;
        bool ok = true;
        for (int i=0; i < a[x].size(); i++) {
            int pos = a[x][i];
            while (i+1 < a[x].size() && a[x][i+1] - a[x][i] < d) i++;

            last = max(last, a[x][i] - d + 1);
            if (last > pos) ok = false;
            last += 2*d;
        }
        if (ok) {
            cout << x << '\n';
            break;
        }
    }
}
