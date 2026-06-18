#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);

    int n; cin>>n;
    unordered_map<string,int> state; // 0: new 1: picked up 2: dropped off
    while(n--) {
        string kind,item; cin>>kind>>item;
        if(kind[0]=='p') { // pickup
            if(state[item]!=0) cout << "no\n", exit(0);
        } else { // dropoff
            if(state[item]!=1) cout << "no\n", exit(0);
        }
        state[item]++;
    }

    for(auto [k,v] : state)
        if(v!=2) cout << "no\n", exit(0);

    cout << "yes\n";
}
