#include<bits/stdc++.h>
using namespace std;

const long long MAXN = 2000000;
const long long MAXK = 6000;
const long long M = 1000000007;
long long n, k;

long long members[MAXN];
long long partials[MAXK];
long long fac[MAXN];

long long mod_mult(long long a, long long b){
    return (a * b) % M;
}

long long mod_sub(long long a, long long b){
    return (M - b + a) % M;
}

long long dp[MAXK]; // dp[c] is #perms of [1..members[c]] where *all* clans are needed for a revolt

int main(){
    cin >> n >> k;

    for(int c = 0; c < k; c++) cin >> members[c];

    fac[0] = 1;
    for(int i=1; i<=n; i++) fac[i] = mod_mult(fac[i-1], i);

    partials[0] = members[0]; // partials[i] = members[0] + ... + members[i]
    for(int c = 1; c < k; c++) partials[c] = partials[c-1] + members[c];

    long long res = fac[n];

    for(int c = 0; c < k; c++){
        dp[c] = fac[partials[c]];
        for(int cc = 0; cc < c; cc++) dp[c] = mod_sub(dp[c], mod_mult(dp[cc], fac[partials[c] - partials[cc]]));
        res = mod_sub(res, mod_mult(dp[c], fac[n - partials[c]]));
    }   
    cout << res << endl;
}
