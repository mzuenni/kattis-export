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
        cin >> in;
        if(in == "W")return 0;
        if(in == "I")cout << 1 << " " << ++I;
        if(in == "J")cout << ((J++*2)+3) % 4 << " " << 3;
        if(in == "L")cout << ((L++*2)+1) % 4 << " " << 5;
        if(in == "O")cout << ((O++*4)+1) % 4 << " " << 7;
        if(in == "S")cout << ((S++*4)+1) % 4 << " " << 7;
        if(in == "T")cout << ((T++*4)+1) % 4 << " " << 9;
        if(in == "Z")cout << ((Z++*4)+1) % 4 << " " << 9;
        cout << endl << flush;
    }
    return 0;
}
