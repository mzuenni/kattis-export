#include <list>
#include <map>
#include <stack>
#include <queue>
#include <set>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cfloat>
#include <numeric>
#include <iomanip>
#include <cassert>
#include <unordered_set>
#include <unordered_map>
#include <bitset>
#include <tuple>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<string> vs;
typedef pair<int,int> pii;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;

#define sz(c) int((c).size())
#define all(c) (c).begin(), (c).end()
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define FORD(i,a,b) for (int i = int(b)-1; i >= (a); i--)
#define FORIT(i,c) for (auto i=(c).begin(); i!=(c).end(); i++)
#define mp make_pair
#define pb push_back
#define has(c,i) ((c).find(i) != (c).end())
#define DBG(...) ({ if(1) fprintf(stderr, __VA_ARGS__); })
#define DBGDO(X) ({ if(1) cerr << "DBGDO: " << (#X) << " = " << (X) << endl; })

struct Point { 
	union {   
		ll a[2];
		struct { ll x,y; };
	};
	Point(ll i=0,ll j=0) : a{i,j} {}  
	ll & operator[](size_t i) { return a[i]; } 
	const ll & operator[](size_t i) const { return a[i]; }
}; 
		
int ccw(Point a, Point b, Point p) { 
	ll c = (b.x - a.x) * (p.y - a.y) - (p.x - a.x) * (b.y - a.y);
	if (abs(c) <= eps) return 0; 
	return (c > 0) ? 1 : -1;
}

bool PointInBox(Point p, Point a, Point b) { 
	return p.x >= min(a.x, b.x) - eps && p.x <= max(a.x, b.x) + eps && 
		p.y >= min(a.y, b.y) - eps && p.y <= max(a.y, b.y) + eps;
}

#define PointOnLine(P,A,B) (ccw(A,B,P)==0)
#define PointOnSegment(P,A,B) (PointOnLine(P,A,B) && PointInBox(P,A,B))

bool SegmentsIntersectStrictly(Point a, Point b, Point s, Point t) { 
	return ccw(a, b, s) * ccw(a, b, t) < 0 &&    
		ccw(s, t, a) * ccw(s, t, b) < 0;
}

bool SegmentsIntersect(Point a, Point b, Point s, Point t) {  
	return SegmentsIntersectStrictly(a, b, s, t) ||   
		PointOnSegment(a, s, t) ||
		PointOnSegment(b, s, t) ||
		PointOnSegment(s, a, b) ||   
		PointOnSegment(t, a, b);
}

bool inside(Point *poly, int n, Point q) { 
	Point far(q.x + 1, q.y); 
	int st = -1;
	FOR(i, 0, n) { 
		if (PointOnSegment(q, poly[i], poly[(i+1)%n])) return true;
		far.x = max(far.x, poly[i].x + 1);  
		if (abs(poly[i].y - q.y) > eps) st = i;
	}
	if (st == -1) return false;  
	int par = 0, last = st;  
	do { 
		int cur = (last + 1) % n;  
		bool special = false;  
		while (PointOnSegment(poly[cur], q, far)) {   
			special = true;
			cur = (cur + 1) % n;  
		}
		if ((poly[last].y - q.y) * (poly[cur].y - q.y) < 0) {  
			if (special || ccw(poly[last], poly[cur], far) * 
				ccw(poly[last], poly[cur], q) < 0) { 
					par = 1-par;  
			}
		}
		last = cur;  
	} while (last != st);
	return par;
}

Point a[50][50];
int l[50];

int main() { 
	ios_base::sync_with_stdio(false); 
	
	int T;
	cin >> T;
	FOR(t,0,T) {
		int p;
		cin >> p;
		FOR(i,0,p) {
			cin >> l[i];
			FOR(j,0,l[i]) {
				cin >> a[i][j].x >> a[i][j].y;
			}
			l[i]--;
		}
		
		bool go = true;
		
		FOR(i,0,p)
			if (a[i][0].x != a[i][l[i]].x ||
				a[i][0].y != a[i][l[i]].y)
					go = false;

		FOR(i,0,p) FOR(j1,0,l[i]) FOR(j2,0,l[i])
			if (abs(j1-j2) > 1 &&
				abs(j1-j2) < l[i]-1 && 
				SegmentsIntersect(a[i][j1],a[i][j1+1],a[i][j2],a[i][j2+1]))
					go = false;

		if (!go) {
			cout << "INVALID POLYGON" << endl;
			continue;
		}
		
		FOR(i1,0,p) FOR(i2,i1+1,p) FOR(j1,0,l[i1]) FOR(j2,0,l[i2])
			if (SegmentsIntersect(a[i1][j1],a[i1][j1+1],a[i2][j2],a[i2][j2+1]))
				go = false;

		if (!go) {
			cout << "INTERSECTING POLYGONS" << endl;
			continue;
		}

		FOR(i1,0,p) {
			int cnt = 0;
			FOR(i2,0,p) {
				if (i1 != i2 && inside(a[i2],l[i2],a[i1][0])) cnt++;
			}
			if (cnt >= 2) go = false;
		}

		if (!go) {
			cout << "INVALID NESTING" << endl;
			continue;
		}

		cout << "CORRECT" << endl;

	}

}

