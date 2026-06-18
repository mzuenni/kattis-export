#include<bits/stdc++.h>
using namespace std;

struct Entity{
    int id;
    int slack;
    bool active = true;
    vector<Entity*> adj;

    Entity(int a, int b):id(a), slack(b)
    {}
};

vector<Entity> entities;

priority_queue<pair<int, Entity*>> q;


int main(){
    int num_p, num_b, c;
    cin >> num_b >> num_p >> c;

    for(int p = 0; p < num_p; p++) entities.push_back(Entity(p, 0));
    for(int b = 0; b < num_b; b++) entities.push_back(Entity(num_p + b, -c));

    for(int p=0; p < num_p; p++){
        int d;
        cin >> d;
        Entity &ep = entities[p];
        for(int j=0; j<d; j++){
            int b;
            cin >> b;
            b--;
        
            Entity &eb = entities[num_p + b];
            ep.adj.push_back(&eb);
            eb.adj.push_back(&ep);
            eb.slack += 1;
        }
        ep.slack = ep.adj.size()/ 2;         
    }

    for(auto &ep : entities) q.push({-ep.slack, &ep});

    while(!q.empty()){
        auto [slack, e] = q.top();
        q.pop();
        slack = -slack;

        if(slack >= 0) break;
        if(!e->active) continue;

        e->active = false;
        // now decrease the slack of all adjacent entities
        for(Entity* nb : e->adj){
            if(!nb->active) continue;
            nb->slack -= 1;
            q.push({-(nb->slack), nb});
        }
    }

    vector<int> lineup;
    for(int b = 0; b < num_b; b++){
        if(entities[num_p + b].active) lineup.push_back(b);
    }

    if(lineup.empty()){
        cout << "impossible" << endl;
    } else {
        cout << "possible" << endl;
        cout << lineup.size() << endl;
        for(int b : lineup) cout << b + 1<< " ";
        cout << endl;
    }
}