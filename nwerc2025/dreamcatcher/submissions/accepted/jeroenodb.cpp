#include <iostream>
#include <numeric>
using namespace std;

int main() {
    int n; cin >> n;
    for(int k=n/2;k<n;++k) {
        if(gcd(k,n)==1) {
            cout << k << '\n';
            break;
        }
    }
}