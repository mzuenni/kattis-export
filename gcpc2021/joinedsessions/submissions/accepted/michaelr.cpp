#include<bits/stdc++.h>
using namespace std;

pair<int, int> times[1500000];
int leftmost[1500000]; // leftmost adjacent interval of i (including itself)
int rightmost[1500000]; // rightmost adjacent interval of i (including itself)
int rightdis[1500000]; // rightmost disjoint interval smaller than i
int dp[1500000][5];

int main(){
    int n;
    cin >> n;

    for(int i=1; i<=n; i++){
        int a, b;
        cin >> a >> b;
        times[i] = {a, b};
    }
    sort(times + 1, times + n+1);

    // precomputation
    int left = 1, right = n;
    for(int i=1; i<=n; i++){
        while(times[left].second < times[i].first) left++;
        leftmost[i] = left;
        while(times[right].first > times[n-i].second) right--;
        rightmost[n-i] = right;
    }
    memset(rightdis, 0, sizeof(rightdis));
    for(int i=1; i<=n; i++) {
        if(rightmost[i] == n) continue;
        rightdis[rightmost[i] + 1] = i;
    }
    for(int i=1; i<=n; i++) if(rightdis[i] == 0) rightdis[i] = rightdis[i-1];
    for(int i=1; i<=n; i++) for(int k=0; k<5; k++) dp[i][k] = 2*n;
    for(int k= 0; k<5; k++) dp[0][k] = 0;

    // DP
    for(int i=1; i<=n; i++){
        for(int k= 0; k<4; k++){
            dp[i][k] = dp[rightdis[leftmost[i]]][k] + 1;
            if(k > 0) dp[i][k] = min(dp[i][k], dp[leftmost[i]][k-1]);
        }
    }

    // output
    for(int k=1;  k<=3; k++) if(dp[n][k] < dp[n][0]){
        cout << k << endl;
        return 0;
    }
    cout << "impossible" << endl;
    return 0;
}