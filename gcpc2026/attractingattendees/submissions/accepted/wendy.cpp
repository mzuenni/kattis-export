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

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

    ll bands, people, c, k;
    cin >> bands >> people >> c;
    vector<vl> bandsEdges(bands), peopleEdges(people);
    vl degBands(bands, 0), degPeople(people, 0);
    for0(i, people) {
        cin >> k;
        ll b;
        for0(j, k) {
            cin >> b;
            b--;
            bandsEdges[b].pb(i);
            degBands[b]++;
            peopleEdges[i].pb(b);
            degPeople[i]++;
        }
    }
    queue<ll> qPeople, qBands;
    for0(i, bands) {
        if (sz(bandsEdges[i]) < c) qBands.push(i);
    }
    vector<bool> removed(bands, false);
    while (!qPeople.empty() || !qBands.empty()) {
        while (!qPeople.empty()) {
            ll remove = qPeople.front();
            qPeople.pop();
            for (ll b : peopleEdges[remove]) {
                if (degBands[b] == c) qBands.push(b);
                degBands[b]--;
            }
        }
        while (!qBands.empty()) {
            ll remove = qBands.front();
            removed[remove] = true;
            qBands.pop();
            for (ll p : bandsEdges[remove]) {
                if (degPeople[p] == (sz(peopleEdges[p]) + 1) / 2) qPeople.push(p);
                degPeople[p]--;
            }
        }
    }
    if (count(removed.begin(), removed.end(), false) == 0) cout << "impossible" << endl;
    else {
        cout << "possible" << endl;
        cout << count(removed.begin(), removed.end(), false) << endl;
        for0(i, bands) {
            if (!removed[i]) cout << i + 1 << endl;
        }
    }
}
