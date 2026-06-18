#include<bits/stdc++.h>
using namespace std;

set<string> bag;
set<string> dropped;

void reject(){
    cout << "no" << endl;
    exit(0);
}

int main(){
    int n;
    cin >> n;


    for(int i=0; i<n; i++){
        string op, item;
        cin >> op >> item;
        if(op == "pickup"){
            if(bag.count(item) > 0 || dropped.count(item) > 0) reject();
            bag.insert(item);
        } else{
            if(!bag.count(item)) reject();
            dropped.insert(item);
            bag.erase(item);
        }
    }

    if(bag.size() > 0) reject();

    cout << "yes" << endl;
}