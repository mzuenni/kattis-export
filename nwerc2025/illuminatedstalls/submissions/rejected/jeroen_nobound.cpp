// @EXPECTED_RESULTS@: TIME_LIMIT_EXCEEDED, RUN_TIME_ERROR
#include <iostream>
#include <complex>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>
#include <array>
using namespace std;

#define all(x) begin(x),end(x)
typedef vector<int> vi;

typedef complex<int> pt;
#define X real()
#define Y imag()
int manh(pt p) {
    return abs(p.X)+abs(p.Y);
}
bool comp(pt a, pt b) {
    return (a.X==b.X?a.Y<b.Y:a.X<b.X);
}

bool ans;
void yep() {
    ans = true;
}

vector<vi> adj;
struct S { // segment
    pt a,b;
    int id;
    void read() {
        int x,y;
        cin >> x >> y;
        a = {x,y};
        cin >> x >> y;
        b = {x,y};
    }
    void rot() {
        a*=pt{0,1};
        b*=pt{0,1};
        if(!comp(a,b)) {
            reverse(all(adj[id]));
            swap(a,b);
        }
    }
    int len() const {
        return manh(a-b);
    }
};


void solveU(S base, const vector<S>& seg, const vi& biggest) {
    auto getid = [&](int i, int y) {
        auto it = lower_bound(all(adj[i]),y,[&](int j, int y) {
            return seg[j].a.Y<y;
        });
        if(it!=adj[i].end() and seg[*it].a.Y==y) return *it;
        return -1;
    };

    auto check = [&](int i, int j) {
        int side = seg[j].a.X-seg[i].b.X;
        int ywant = side+base.a.Y;
        array<int,2> lr = {getid(i,ywant),getid(j,ywant)};
        if(lr[0]!=-1 and lr[0]==lr[1]) { yep(); return; }
        for(int msk=0;msk<4;++msk) {
            auto tmp = lr;
            for(int j=0;j<2;++j) if(1<<j & msk) tmp[j]=-1;
            int left =   (tmp[1]==-1?seg[j].a.X:seg[tmp[1]].a.X)  - (tmp[0]==-1?seg[i].a.X:seg[tmp[0]].b.X);
            for(int b : biggest) {
                if(!count(all(tmp),b) and b!=i and b!=j and b!=base.id) {
                    if(seg[b].len()>=left) {
                        yep();
                        return;
                    }
                    break;
                }
            }
        }
    };

    struct event {
        int y;
        int x;
        int id;
        bool operator<(const event& o) {
            return y>o.y;
        }
    };

    vector<event> events;
    for(int j : adj[base.id]) {
        auto& os = seg[j];
        events.push_back({os.b.Y-base.a.Y, os.b.X,os.id});
    }
    sort(all(events));
    map<int,int> active;
    for(auto e : events) {
        auto it = active.lower_bound(e.x);
        auto it2 = it;
        while(it!=active.end()) { // this loop can run at most 2 times, because it will output 'yes' otherwise
            if(it->first-e.x > e.y) break;
            // check it
            check(e.id, it->second);
            if (ans) return;
            it++;
        }
        it=it2;
        while(it!=active.begin()) {  // same with this.
            --it;
            if(e.x-it->first>e.y) break;
            check(it->second,e.id);
            if (ans) return;
        }
        active[e.x]=e.id;
    }
                    
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        ans = false;
        int n; cin >> n;

        adj.assign(n, {});
        long long intersections=0;
        auto add = [&](int i, int j) {
            // if(++intersections) {
            //     yep();
            // }
            ++intersections;
            adj[i].push_back(j);
            adj[j].push_back(i);
        };
        vector<S> seg(n);
        for(int i=0;i<n;++i) {
            seg[i].read();
            seg[i].id=i;
        }
        vi biggest(n);
        iota(all(biggest),0);
        sort(all(biggest),[&](int i, int j) {return seg[i].len()>seg[j].len();});
        biggest.resize(min(n, 6));

        struct event {
            int id;
            int x,y1,y2;
            int sgn;
            bool operator<(const event& o) {
                if(x==o.x) {
                    return sgn>o.sgn;
                }
                return x<o.x;
            }
        };
        vector<event> es;
        for(auto s : seg) {
            if(s.a.Y==s.b.Y) {
                // horizontal segment
                es.push_back({s.id,s.a.X,s.a.Y,s.a.Y,1});
                es.push_back({s.id,s.b.X,s.b.Y,s.b.Y,-1});
            } else {
                es.push_back({s.id,s.a.X,s.a.Y,s.b.Y,0});
            }
        }
        sort(all(es));
        map<int,int> active;
        for(auto e : es) {
            if(e.sgn==0) { // query
                auto it = active.lower_bound(e.y1);
                while(it!=active.end() and it->first<=e.y2) {
                    add(it->second,e.id);
                    if (ans) goto done;
                    it++;
                }
            } else {  // update
                if(e.sgn==1) active[e.y1]=e.id;
                else active.erase(e.y1);
            }
        }

        for(int rot=0;rot<4;++rot) {
            for(auto& s : seg) if(s.a.Y==s.b.Y) {
                solveU(s,seg,biggest);
                if (ans) goto done;
            }
            for(auto& s : seg) s.rot();
        }
done:   cout << (ans ? "yes\n" : "no\n");
    }

}
