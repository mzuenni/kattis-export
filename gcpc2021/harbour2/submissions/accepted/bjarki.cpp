#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <cassert>
using namespace std;
#define rep(i,a,b) for (auto i=(a); i<(b); ++i)
typedef pair<int, int> ii;

set<ii> arr;

bool on_top(int at) {
    auto it = arr.lower_bound(ii(at, -1));
    if (it == arr.end()) return false;
    if (it->second == 0) return true;
    ++it;
    if (it == arr.end()) return false;
    if (it->second == 0) return true;
    return false;
}

int main() {
    int n, l, r;
    cin >> n >> l >> r;

    int at = l-1;

    map<int,int> idx;
    rep(i,0,l) {
        int x;
        cin >> x;
        idx[x] = i;
        arr.insert(ii(idx[x], x));
    }
    rep(i,0,r) {
        int x;
        cin >> x;
        idx[x] = n-i;
        arr.insert(ii(idx[x], x));
    }

    arr.insert(ii(-1, -1));
    arr.insert(ii(n+1, -1));

    int cnt = on_top(at) ? 1 : 0;
    rep(x,1,n+1) {
        int i = idx[x];
        auto it = arr.lower_bound(ii(i, -1));
        assert(it != arr.end() && it->first == i);
        --it;
        at = it->first;
        ++it;
        arr.erase(it);
        if (on_top(at)) cnt++;
    }

    cout << cnt << endl;

    return 0;
}

