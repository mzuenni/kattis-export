#include<bits/stdc++.h>

using namespace std;

long double sides[5] = {4, 6, 8, 12, 20};
long double dice[5];
long double dp[1000];
vector<pair<long double, int>> res;

int main(){
    for(int i=0; i<5; i++) cin >> dice[i];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;

    for(int i=0; i<5; i++){ 
        for(int j=0; j<dice[i]; j++){ // iterate over all dice 
            for(int val = 999; val >= 0; val--){
                dp[val] = 0;
                for(int s = 1; s <= sides[i] && s <= val; s++) dp[val] += dp[val - s] / sides[i];
            }
        }
    }

    for(int i=0; i<1000; i++) if(dp[i] > 0) res.push_back({1 - dp[i], i});
    sort(res.begin(), res.end());

    for(auto p : res) cout << p.second << " ";
    cout << endl;
}