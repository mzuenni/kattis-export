#include <bits/stdc++.h>
using namespace std;

#define sz(c) int((c).size())
#define all(c) (c).begin(), (c).end()
#define FOR(i,a,b) for (int i = (a); i < (b); i++)

vector<vector<pair<char, int> > > adj1, adj2;

int N2,N1;
unordered_map<string,int> mm;
int getid(string in){
    if(mm.find(in) == mm.end())mm[in] = N2++;
    if(N2 > sz(adj2))adj2.resize(N2);
    return mm[in];
}

void parseGraph(int id, string options){
    for(char c: options){
        cout << "W " << c << endl << flush;
        string oname, ooptions;
        cin >> oname >> ooptions;
        int oldN2 = N2;
        int oid = getid(oname);
        if(oldN2 != N2){
            if(N2 > N1)return;
            parseGraph(oid, ooptions);
            if(N2 > N1)return;
        }
        adj2[id].push_back({c,oid});
        cout << "W " << c << endl << flush;
        cin >> oname >> ooptions;
    }
}
void parseGraph(){
    string name,options;
    cin >> name >> options;
    int id = getid(name);
    parseGraph(id, options);
}

bool check_equality(int sn){
    vector<int> indices(N1,-1);
    indices[sn] = 0;
    queue<int> q;
    q.push(sn);
    while(!q.empty()){
        int n1 = q.front();
        q.pop();
        int n2 = indices[n1];
        if(adj1[n1].size() != adj2[n2].size())return false;
        FOR(i,0,sz(adj1[n1])){
            auto ed1 = adj1[n1][i];
            auto ed2 = adj2[n2][i];
            if(ed1.first != ed2.first)return false;
            if(indices[ed1.second] == -1){
                indices[ed1.second] = ed2.second;
                q.push(ed1.second);
            } else {
                if(indices[ed1.second] != ed2.second)return false;
            }
        }
    }
    return true;
}

int main(){
    cin >> N1;
    adj1.clear();
    adj1.resize(N1);
    FOR(i,0,N1){
        int M;
        cin >> M;
        FOR(j,0,M){
            int to;
            string path;
            cin >> path >> to;
            adj1[i].push_back({path[0], to-1});
        }
        sort(all(adj1[i]));
    }
    N2 = 0;
    mm.clear();
    adj2.clear();
    adj2.resize(N1);
    parseGraph();
    FOR(n,0,N2)sort(all(adj2[n]));
    if(N1 != N2){
        cout << "R no\n";
        return 0;
    }
    int match = -1;
    FOR(sn,0,N1){
        if(check_equality(sn)){
            if(match == -1)match = sn;
            else match = -2;
        }
    }
    if(match == -1)cout << "R no\n" << flush;
    else if(match == -2)cout << "R ambiguous\n" << flush;
    else cout << "R "<< match+1 << endl << flush;
    return 0;
}
