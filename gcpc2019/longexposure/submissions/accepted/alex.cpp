#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;

#define sz(c) int((c).size())
#define all(c) (c).begin(), (c).end()
#define FOR(i,a,b) for (int i = (a); i < (b); i++)

const int MAXN = 1024;
pll X[MAXN],Y[MAXN];
int N;
int getid(ll v, const vector<ll> & co){
    int lo = 0, hi = sz(co);
    while(lo != hi){
        int m = lo + (hi - lo) / 2;
        if(co[m] == v)return m;
        if(co[m] < v)lo = m + 1;
        else hi = m;
    }
    assert(co[lo] == v);
    return lo;
}

vector<pll> condense(vector<pll> intervals){
    sort(all(intervals));
    vector<pll> res;
    assert(!intervals.empty());
    ll f = intervals[0].first, t = intervals[0].second;
    for(auto p: intervals){
        if(t >= p.first)t = max(t, p.second);
        else {
            res.push_back({f,t});
            tie(f,t)=tie(p.first, p.second);
        }
    }
    res.push_back({f,t});
    return res;
}

int main(){
    cin >> N;
    set<ll> XS={(ll)-1.01e9, 0, (ll)1.01e9}, YS={(ll)-1.01e9, 0, (ll)1.01e9};
    FOR(i,0,N){
        cin >> X[i].first >> Y[i].first >> X[i].second >> Y[i].second;
        X[i].second += X[i].first;
        Y[i].second += Y[i].first;
        XS.insert(X[i].first);
        XS.insert(X[i].second);
        YS.insert(Y[i].first);
        YS.insert(Y[i].second);
    }
    vector<ll> XV(all(XS));
    vector<ll> YV(all(YS));
    int SX = sz(XV), SY = sz(YV);
    vector<vector<bool> > mark(SX, vector<bool>(SY,false));
    FOR(i,0,N){
        int XF = getid(X[i].first, XV), XT = getid(X[i].second, XV);
        int YF = getid(Y[i].first, YV), YT = getid(Y[i].second, YV);
        FOR(x,XF,XT)FOR(y,YF,YT)mark[x][y] = 1;
    }
    vector<pll> black, white;
    FOR(x,0,SX-1){
        FOR(y,0,SY-1){
        ll minx = min(abs(XV[x]),abs(XV[x+1])), maxx = max(abs(XV[x]),abs(XV[x+1]));
        ll miny = min(abs(YV[y]),abs(YV[y+1])), maxy = max(abs(YV[y]),abs(YV[y+1]));
        ll lo = minx*minx+miny*miny, hi = maxx*maxx+maxy*maxy;
        if(mark[x][y])black.push_back({lo,hi});
        else white.push_back({lo,hi});
        }
    }
    black = condense(black);
    white = condense(white);
    ll resblack = 0, resgray = 0;
    int D = 0;
    for(auto p: black){
        while(D < sz(white) && white[D].second <= p.second){
            if(white[D].second > p.first){
                white[D].first = max(white[D].first, p.first);
                resblack += white[D].first - p.first;
                resgray += white[D].second - white[D].first;
                p.first = white[D].second;
            }
            D++;
        }
        if(D < sz(white) && white[D].first < p.second){
            white[D].first = max(white[D].first, p.first);
            resgray += p.second - white[D].first;
            p.second = white[D].first;
        }
        resblack += p.second - p.first;
    }
    printf("%.9lf\n%.9lf\n", (double)(acos(-1) * (double)resblack), (double) (acos(-1) * (double)resgray));
    return 0;
}
