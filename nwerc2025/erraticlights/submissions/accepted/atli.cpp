#include<vector>
#include<iostream>
#include<iomanip>
#include<unordered_map>
#include<algorithm>
#include<cfloat>
using namespace std;
typedef vector<int> vi;

struct VectorHasher {
    int operator()(const vector<int> &V) const {
        int hash = V.size();
        for(auto &i : V) {
            hash ^= i + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }
        return hash;
    }
};

int n, k = 3;
unordered_map<vi,double,VectorHasher> memo;

double dp(vi rho) {
    if(rho.size() == 1) return 0.0;
    sort(rho.rbegin(), rho.rend());
    if(memo.count(rho)) return memo[rho];
    int sz = rho.size();
    double w = k; w /= sz - 1;
    rho.back()--;
    bool pop = false;
    if(rho.back() == 0) {
        rho.pop_back();
        pop = true;
    }
    double sm = 0.0;
    for(int i = 0; i + 1 < sz; ++i) {
        rho[i]++;
        sm += dp(rho);
        rho[i]--;
    }
    sm /= sz - 1;
    sm += w;
    if(pop) rho.push_back(0);
    rho.back()++;
    // for(int x : rho) cout << x << ' ';
    // cout << ": " << sm << endl;
    return memo[rho] = sm;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s;
    cin >> n >> s;
    vi rho(k);
    string colours = "rgb";
    for(char c : s) {
        rho[colours.find(c)]++;
    }
    sort(rho.rbegin(), rho.rend());
    while(rho.back() == 0) rho.pop_back();
    cout << setprecision(15);
    cout << dp(rho) << '\n';
}
