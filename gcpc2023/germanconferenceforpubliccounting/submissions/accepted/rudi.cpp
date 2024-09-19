#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n;

    if(n < 10) {
        cout << n + 1 << endl;
        return 0;
    }

    int count = 0;
    for(int m = 10; m <= n; m*= 10) count++;
    for(int digi = 1; digi <= 9; digi++){
        for(long long m = digi; m <= n; m = 10 * m + digi){
            count++;
        }
    }

    cout << count << endl;
}