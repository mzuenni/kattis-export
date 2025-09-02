#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for (int i = (a); i < (b); i++)
int main(){
    int N,D;
    cin >> N >> D;
    int res = -(N-1)*D;
    FOR(i,0,N){
        string in;
        cin >> in;
        res += 60 * (in[0] - '0') + 10 * (in[2] - '0') + (in[3] - '0');
    }
    printf("%02d:%02d:%02d\n", res / 3600, (res % 3600) / 60, res % 60);
    return 0;
}
