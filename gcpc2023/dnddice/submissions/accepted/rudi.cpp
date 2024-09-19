#include<bits/stdc++.h>
using namespace std;

int sides[5] = {4, 6, 8, 12, 20};
int dice[5];
long double dp[1000];
vector<pair<long double, int>> res;

int main(){
    for(int i=0; i<5; i++) cin >> dice[i];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    int maxval = 0;
    for(int i=0; i<5; i++) maxval += dice[i] * sides[i];

    for(int i=0; i<5; i++){ 
        for(int j=0; j<dice[i]; j++){ // iterate over all dice 
            for(int val = maxval; val >= 0; val--){
                dp[val] = 0;
                for(int s = 1; s <= sides[i] && s <= val; s++) dp[val] += dp[val - s];
            }
        }
    }

    for(int i=0; i <= maxval; i++) if(dp[i] > 0) res.push_back({-dp[i], i});
    sort(res.begin(), res.end());

    for(auto p : res) cout << p.second << " ";
    cout << endl;
}