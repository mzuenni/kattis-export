#include <iostream>
using namespace std;

int main() {
    int h,w,k,i,t; cin >> h >> w >> k >> i >> t;
    k--,i--,t--;
    string ans = "KIT"+string(k,'K') + string(t,'T') + string(i,'I');
    for(int i=0;i<h;++i) {
        cout << ans.substr(i*w,w) << '\n';
    }
}
