#include <bits/stdc++.h>
#define f(i, s, k, l) for (int i = s; i < k; i += l)
#define for0(i, k) f(i, 0, k, 1)

#define pl pair<long long, long long>
#define pb push_back

#define vl vector<long long>
#define vi vector<int>
#define sz(x) (ll)(x).size()

using namespace std;
using ll = long long;
using ld = long double;

ll h, w;

ll index(ll x, ll y) {
    return w * y + x;
}

string kit = "kit";

bool check(string &s) {
    ll count = 0;
    for0(x, w) {
        for0(y, h) {
            for (ll dx = -1; dx <= 1; dx++) {
                for (ll dy = -1; dy <= 1; dy++) {
                    if (x + 2 * dx >= w || x + 2 * dx < 0) continue;
                    if (y + 2 * dy >= h || y + 2 * dy < 0) continue;
                    if (s[index(x + 0 * dx, y + 0 * dy)] != 'k') continue;
                    if (s[index(x + 1 * dx, y + 1 * dy)] != 'i') continue;
                    if (s[index(x + 2 * dx, y + 2 * dy)] != 't') continue;
                    count++;
                }
            }
        }
    }
    return count == 1;
}

string transpose(string &s) {
    string res;
    for0(j, h) {
        for0(i, w) res.pb(s[i * h + j]);
    }
    return res;
}

bool checkTransposed(string &s) {
    string res = transpose(s);
    return check(res);
}

bool checkReverse(string s) {
    reverse(s.begin(), s.end());
    return check(s);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
    vl count(3);
    map<char, ll> c;
    c['k'] = 0;
    c['i'] = 0;
    c['t'] = 0;
    cin >> h >> w >> c['k'] >> c['i'] >> c['t'];

    // ttttkkkkkitiiii
    string res;
    for0(i, c['t'] - 1) res.pb('t');
    for0(i, c['k']) res.pb('k');
    res.pb('i');
    res.pb('t');
    for0(i, c['i'] - 1) res.pb('i');
    // cout << res << endl;
    // res = transpose(res);
    // cout << "sdfölksd" << res << endl;
    // for0(y, h) {
    //     for0(x, w) cout << res[y * w + x];
    //     cout << endl;
    // }
    // cout << endl;

    // iiiikkkkkkitttttt
    if(!check(res) && !checkTransposed(res) && !checkReverse(res)) {
        res = "";
        for0(i, c['i'] - 1) res.pb('i');
        for0(i, c['k']) res.pb('k');
        res.pb('i');
        res.pb('t');
        for0(i, c['t'] - 1) res.pb('t');
    }
    // for0(y, h) {
    //     for0(x, w) cout << res[y * w + x];
    //     cout << endl;
    // }
    // cout << endl;

    // iiiiiitiktttttttt
    if(!check(res) && !checkTransposed(res) && !checkReverse(res)) {
        res = "";
        for0(i, c['i'] - 1) res.pb('i');
        res.pb('t');
        res.pb('i');
        for0(i, c['k']) res.pb('k');
        for0(i, c['t'] - 1) res.pb('t');
    }

    // for0(y, h) {
    //     for0(x, w) cout << res[y * w + x];
    //     cout << endl;
    // }
    // cout << endl;


    //kkkkkkkittttttiiiii
    if(!check(res) && !checkTransposed(res) && !checkReverse(res)) {
        res = "";
        for0(i, c['k']) res.pb('k');
        res.pb('i');
        res.pb('t');
        for0(i, c['t'] - 1) res.pb('t');
        for0(i, c['i'] - 1) res.pb('i');
    }
    // for0(y, h) {
    //     for0(x, w) cout << res[y * w + x];
    //     cout << endl;
    // }
    // cout << endl;

    // kkkkkkitiiiiiiiittttttt
    if(!check(res) && !checkTransposed(res) && !checkReverse(res)) {
        res = "";
        for0(i, c['k']) res.pb('k');
        res.pb('i');
        res.pb('t');
        for0(i, c['i'] - 1) res.pb('i');
        for0(i, c['t'] - 1) res.pb('t');
    }
    // for0(y, h) {
    //     for0(x, w) cout << res[y * w + x];
    //     cout << endl;
    // }
    // cout << endl;

    // kkkkkkkkittttttiiiii
    if(!check(res) && !checkTransposed(res) && !checkReverse(res)) {
        res = "";
        for0(i, c['k']) res.pb('k');
        res.pb('i');
        res.pb('t');
        for0(i, c['t'] - 1) res.pb('t');
        for0(i, c['i'] - 1) res.pb('i');
    }

    // tttttttiiiiiitikkkkkk
    if(!check(res) && !checkTransposed(res) && !checkReverse(res)) {
        res = "";
        for0(i, c['t'] - 1) res.pb('t');
        for0(i, c['i'] - 1) res.pb('i');
        res.pb('t');
        res.pb('i');
        for0(i, c['k']) res.pb('k');
    }

    // itk
    // for0(y, h) {
    //     for0(x, w) cout << res[y * w + x];
    //     cout << endl;
    // }
    // cout << endl;

    if(!check(res) && !checkTransposed(res) && !checkReverse(res)) {
        res = "";
        for0(i, c['i'] - 1) res.pb('i');
        for0(i, c['t']) res.pb('t');
        res.pb('i');
        for0(i, c['k']) res.pb('k');
    }

    if (checkTransposed(res)) res = transpose(res);
    else if (checkReverse(res)) reverse(res.begin(), res.end());
    for0(y, h) {
        for0(x, w) cout << res[y * w + x];
        cout << endl;
    }
    cout << endl;
}
// iiiiikkkkkktttttt
// tki
