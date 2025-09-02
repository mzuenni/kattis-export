#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
    ll x1,y1,x2,y2,m1,m2;
    cin >> x1 >> y1 >> m1 >> x2 >> y2 >> m2;
    ll dx = x2 - x1, dy = y2 - y1, ax = abs(x1-x2), ay = abs(y1-y2);
    if(ax + ay > m1 + m2 || (ax+ay+m1+m2) % 2 == 1){
        cout << "impossible\n";
    } else {
        if(m1 >= ax){
            x1 = x2;
            m1 -= ax;
            if(m1 >= ay){
                y1 = y2;
                m1 -= ay;
                if(m1&1)++y1;
            } else {
                y1 += m1 * (ay / dy);
            }
        } else {
            x1 += m1 * (ax / dx);
        }
        cout << x1 << " " << y1 << endl;
    }
    return 0;
}
