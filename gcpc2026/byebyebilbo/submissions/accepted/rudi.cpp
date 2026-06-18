#include<bits/stdc++.h>
using namespace std;

int n, k;

int next_hole[200000];

vector<int> badj[200000];

vector<int> choices;


int dfs(int i){
    int required_dist = k;
    for(int j: badj[i]){
        required_dist = min(required_dist, dfs(j) - 1);
    }

    if(required_dist == 0 || i == 0){
        choices.push_back(i);
        required_dist = k + 1;
    }
    return required_dist;
}

int main(){
    cin >> n >> k;
    k--;

    for(int i=1; i<n; i++){
        cin >> next_hole[i];
        next_hole[i]--;
        badj[next_hole[i]].push_back(i);
    }

    dfs(0);
    cout << choices.size() << endl;
    for(int i: choices){
        cout << i+1 << " ";
    }
    cout << endl;
}
