#include <bits/stdc++.h>
using namespace std;

int m = 12345;
unordered_map<string,int> id;

vector<int> read_vec() {
    int n; cin >> n;
    vector<int> res(n);
    for (int &x: res) {
        string s; cin >> s;
        char c = s[0];
        if (ssize(s) == 1 && isalpha(c)) {
            x = islower(c) ? c-'a' : c-'A'+26;
        } else {
            if (!id.count(s)) id[s] = m++;
            x = id[s];
        }
    }
    return res;
}

const int N = 5e6;
int M = 1;
unordered_map<int,int> go[N];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    auto s = read_vec();

    int n = s.size();
    for (int i = 0; i < n; i++) {
        int cur = 0, k = 0;
        vector<int> db(52, -1);
        for (int j = i; j < n; j++) {
            int x = s[j];
            if (x < 52) {
                if (db[x] < 0) db[x] = k++;
                x = db[x];
            }
            if (!go[cur].count(x)) go[cur][x] = M++;
            cur = go[cur][x];
        }
    }

    int q; cin >> q;
    while (q--) {
        auto t = read_vec();
        int cur = 0, k = 0;
        vector<int> db(52, -1);
        for (int x: t) {
            if (x < 52) {
                if (db[x] < 0) db[x] = k++;
                x = db[x];
            }
            if (!go[cur].count(x)) {
                cur = -1;
                break;
            }
            cur = go[cur][x];
        }
        cout << (cur >= 0 ? "yes" : "no") << '\n';
    }
}
