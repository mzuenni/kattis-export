#include<iostream>

using namespace std;

const long long MOD = 1000000007;

long long a[5005];
long long T[5005];
long long f[1000005];

int main()
{
    int n, k;
    cin >> n >> k;

    f[0] = 1;
    for(int i = 1; i <= n; ++i) {
        f[i] = (f[i-1] * i) % MOD;
    }

    for(int i = 1; i <= k; ++i) {
        cin >> a[i];
        a[i] += a[i-1];
    }
    a[k+1] = n;

    for(int i = 1; i <= k+1; ++i) {
       T[i] = f[a[i]];
       for(int j = 1; j < i; ++j) {
           T[i] = (T[i] + (MOD - (f[a[i] - a[j]] * T[j] % MOD))) % MOD;
       }
    }

    cout << T[k+1] << endl;
}
