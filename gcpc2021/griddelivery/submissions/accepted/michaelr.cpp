#include<bits/stdc++.h>
using namespace std;

vector<int> mep[3000];
int main(){
    int w, h;
    cin >> h >> w;

    for(int i=0; i<h; i++) for(int j=0; j<w; j++){
        char c;
        cin >> c;
        if (c == 'C') mep[i].push_back(j);
    }
    int c = 0, res = 0;
    for(int i=0; i<h; i++) c += mep[i].size();

    while(c > 0){ // (start at (0, 0), take coins on upper border
        int newFront = 0;
        int front = 0;
        for(int i = res; i<h; i++){
            while(mep[i].size() > 0 && mep[i].back() >= front){
                newFront = max(newFront, mep[i].back());
                mep[i].pop_back();
                c--;
            }
            front = newFront;
        }
        res++;
    } 
    cout << res << endl;
}
