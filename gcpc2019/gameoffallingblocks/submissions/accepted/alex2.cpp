#include <bits/stdc++.h>
using namespace std;
#define all(c) (c).begin(), (c).end()

int main(){
    int I=0, J=0, L=0, O=0, S=0, T=0, Z=0;
    while(true){
        vector<int> nums = {I,J,L,O,S,T,Z};
        sort(all(nums));
        reverse(all(nums));
        assert(nums[0] <= 2);
        string in;
        assert(cin >> in);
        if(in == "W"){return 0;}
        if(in == "I"){++I;cout << "1 1";}
        if(in == "J"){++J;cout << ((L==0)?"0 2":"3 2");}
        if(in == "L"){++L;cout << ((J==0)?"0 2":"1 3");}
        if(in == "O"){++O;cout << "1 5";}
        if(in == "S"){++S;cout << "1 7";}
        if(in == "T"){++T;cout << "1 9";}
        if(in == "Z"){++Z;cout << "1 5";}
        cout << endl << flush;
    }
    return 0;
}
