#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

#define rep(a, b)   for(int a = 0; a < (b); ++a)
#define all(a)      begin(a),end(a)

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);

    int n; cin>>n;
    set<string> items;
    vector<pair<string,bool>> schedule(n);
    for(auto& [name, is_dropoff] : schedule) {
        string s; cin>>s>>name;
        is_dropoff = s == "dropoff";
        items.insert(name);
    }

    for(auto& item : items) {
        auto pck = pair(item, false);
        auto drp = pair(item, true);
        auto cnt_p = count(all(schedule), pck);
        auto cnt_d = count(all(schedule), drp);
        auto first_p = find(all(schedule), pck);
        auto first_d = find(all(schedule), drp);
        if(cnt_p != 1 || cnt_d != 1 || first_p > first_d) {
            cout << "no\n";
            return 0;
        }
    }

    cout << "yes\n";
}
