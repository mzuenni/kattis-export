#include "bits/stdc++.h"

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    long long t;
    cin >> t;
    for (long long i = 0; i < t; i++) {
        long long n, h;
        cin >> n >> h;
        vector<vector<long long>> adjList(n);
        vector<long long> deg(n);
        for (long long j = 0; j < h; j++) {
            long long a, b;
            cin >> a >> b;
            a--;
            b--;
            adjList[a].push_back(b);
            deg[b]++;
        }
        vector<long long> ready;
        for (long long j = 0; j < n; j++) {
            if (deg[j] == 0) {
                ready.push_back(j);
            }
        }
        bool unique = true;
        vector<long long> res;
        while (!ready.empty()) {
            unique &= ready.size() == 1;
            long long c = ready.back(); ready.pop_back();
            res.push_back(c);
            for (long long n : adjList[c]) {
                deg[n]--;
                if (deg[n] == 0) {
                    ready.push_back(n);
                }
            }
        }
        if (res.size() != n) {
            cout << "recheck hints" << endl;
        } else if (!unique) {
            cout << "missing hints" << endl;
        } else {
            for (long long x : res) {
                cout << (x + 1) << " ";
            }
            cout << endl;
        }

    }
}
