#include<bits/stdc++.h>
using namespace std;

#define correct first
#define guessed second

const int MAXN = 3005;
long long M = 998244353;
int n;

long long mod_inv(long long a){
    long long res = 1;
    long long n = M - 2;
    while(n){
        if(n%2 == 1) res = res * a % M;
        n = n / 2;
        a = a * a % M;
    }
    return res;
}

long long inv[MAXN];

long long a[MAXN];
long long b[MAXN];
long long dp[MAXN][MAXN];

// l_partition[l][r] is the set of l-feasible indices i with first_r[i] = r
vector<int> l_partition[MAXN][MAXN];
vector<int> r_partition[MAXN][MAXN];

int first_r[MAXN]; // first_r[i] is the smallest r s.t. i is r-feasible
int first_l[MAXN];

long long l_sum[MAXN][MAXN]; // sums of the form \sum_i{dp[l][i]}
long long r_sum[MAXN][MAXN]; // sums of the form \sum_i{dp[i][r]}
long long n_feasible[MAXN][MAXN];

bool is_l_feasible(int i, int l){
    if(l > n) return false;
    if(l == 0) return true;
    return i > l && b[i] >= a[l];
}

bool is_r_feasible(int i, int r){
    if(r > n) return true;
    if(r == 0) return false;
    return i < r && b[i] <= a[r];
}

bool is_l_r_feasible(int i, int l, int r){
    return is_l_feasible(i, l) && is_r_feasible(i, r);
}

long long get_dp(int l, int r);

long long l_partition_val(int l, int r){
    long long res = 0;
    for(int i: l_partition[l][r]) res = (res + get_dp(l, i)) % M;
    return res;
}

long long r_partition_val(int l, int r){
    long long res = 0;
    for(int i: r_partition[l][r]) res = (res + get_dp(i, r)) % M;
    return res;
}

long long get_l_sum(int l, int r){
    if(l_sum[l][r] < 0){
        long long next_term = l_partition_val(l, r);
        if(l == r) l_sum[l][r] = next_term;
        else l_sum[l][r] = (get_l_sum(l, r-1) + next_term) % M;
    }
    return l_sum[l][r];
}

long long get_r_sum(int l, int r){
    if(r_sum[l][r] < 0){
        long long next_term = r_partition_val(l, r);
        if(l == r) r_sum[l][r] = next_term;
        else r_sum[l][r] = (get_r_sum(l+1, r) + next_term) % M;
    }
    return r_sum[l][r];
}


long long get_dp(int l, int r){
    if(dp[l][r] < 0){
        long long feasible = n_feasible[l][r];
        if(feasible == 0) dp[l][r] = 0;
        else {
            long long lsum = get_l_sum(l, r);
            long long rsum = get_r_sum(l, r);
            long long sums = (lsum + rsum) % M;
            dp[l][r] = (1 + sums * inv[feasible]) % M;
        }
    }
    return dp[l][r];
}

vector<pair<int, int>> input;

int main(){
    cin >> n;

    for(int i=1; i<=n; i++) inv[i] = mod_inv(i);

    for(int i=0; i<n; i++){
        int a, b;
        cin >> a >> b;
        input.push_back({a, b});
    }

    sort(input.begin(), input.end());

    // a and b are indexed from 1 to n
    for(int i=0; i<n; i++){
        a[i+1] = input[i].first;
        b[i+1] = input[i].second;
    }

    memset(dp, -1, MAXN * MAXN * sizeof(long long));
    memset(l_sum, -1, MAXN * MAXN * sizeof(long long));
    memset(r_sum, -1, MAXN * MAXN * sizeof(long long));

    // compute first_r and first_l
    for(int i=1; i<=n; i++){
        first_r[i] = n+1;
        while(is_r_feasible(i, first_r[i] - 1)) first_r[i]--;

        first_l[i] = 0;
        while(is_l_feasible(i, first_l[i] + 1)) first_l[i]++;
    }


    // fill l_partition
    for(int l = 0; l<=n; l++){
        for(int i=1; i <= n; i++){
            if(!is_l_feasible(i, l)) continue;
            int r = max(l, first_r[i]);
            l_partition[l][r].push_back(i);
        }
    }

    // fill_r_partition
    for(int r=n+1; r >= 1; r--){
        for(int i = 1; i<=n; i++){
            if(!is_r_feasible(i, r)) continue;
            int l = min(r, first_l[i]);
            r_partition[l][r].push_back(i);
        }
    }

    // fill n_feasible
    for(int l = 0; l<=n; l++){
        n_feasible[l][l] = l_partition[l][l].size();
        for(int r = l+1; r <= n+1; r++){
            n_feasible[l][r] = n_feasible[l][r-1] + l_partition[l][r].size();
        }
    }  
    
    // fill dp table
    cout << get_dp(0, n+1) << endl;

}