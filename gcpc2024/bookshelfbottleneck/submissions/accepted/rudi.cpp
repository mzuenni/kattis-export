#include "bits/stdc++.h"

using namespace std;

void reject(){
    cout << "impossible" << endl;
    exit(0);
}

int main(){
    int n, h;
    cin >> n >> h;
    int oo = 1000000001;
    long long res = 0;
    for(int i=0; i<n; i++){
        int x, y, z;
        cin >> x >> y >> z;

        int minim = oo;
        if(x <= h || y <= h) minim = min(minim, z);
        if(y <= h || z <= h) minim = min(minim, x);
        if(x <= h || z <= h) minim = min(minim, y);
        if(minim == oo) reject();
        res += minim;
    }
    cout << res << endl;
}