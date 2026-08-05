#include <list>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cfloat>
#include <climits>
#include <numeric>
#include <iomanip>

using namespace std;

const int oo = 0x3f3f3f3f;
const double eps = 1e-7;
const double PI = 2.0 * acos(0.0);


typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<string> vs;

#define sz(c) int((c).size())
#define all(c) (c).begin(), (c).end()
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define FORS(i,a,b,s) for (int i = (a); i < (b); i=i+(s))
#define FORD(i,a,b) for (int i = int(b)-1; i >= (a); i--)
#define FORIT(i,c) for (__typeof__((c).begin()) i = (c).begin(); i != (c).end(); i++)


typedef double coord;

struct pt{
	coord x,y,z;
	pt():x(0),y(0),z(0){};
	pt(coord _x,coord _y,coord _z):x(_x),y(_y),z(_z){};

	pt operator+(const pt& p) { return pt(x+p.x,y+p.y,z+p.z); }
	pt operator-(const pt& p) { return pt(x-p.x,y-p.y,z-p.z); }
	pt operator^(const pt& p) { return pt(y*p.z - z*p.y,z*p.x - x*p.z,x*p.y - y*p.x); }
	pt operator*(const coord f) { return pt(x*f,y*f,z*f); }
	pt operator/(const coord f) { return pt(x/f,y/f,z/f); }
	coord operator*(const pt& p) { return x*p.x+y*p.y+z*p.z; }
};
double len(pt p) { return sqrt(double(p*p)); }


// return (oo,oo,oo) if there is no intersection
// return (oo,0,0) if the line in on the plane
pt intersectPlaneAndLine(pt normal, pt base, pt dir){
	double nd = normal * dir;
	double nb = - (normal * base);
	if (fabs(nd) < eps) {
		if (fabs(nb) < eps) return pt(oo,0,0);
		else return pt(oo,oo,oo);
	}
	double t = nb / nd;
	
	return base + (dir*t);
}

int main(){
	int n; double d;
	cin >> n >> d;
	pt v1,v2;
	cin >> v1.x >> v1.y >> v1.z;
	cin >> v2.x >> v2.y >> v2.z;
	pt norm = v1 ^ v2;
	
	int poss = 0;
	FOR(i,0,n){
		cin >> v1.x >> v1.y >> v1.z;
		cin >> v2.x >> v2.y >> v2.z;
		//double p; cin >> p;
		// plane intersection
		pt intersect = intersectPlaneAndLine(norm,v1,v2);
		if (intersect.x != oo) {
			double dist = len(intersect);
			double t = dist;
			pt tgt = v1 - v2*t;
			if (fabs(dist-d) < eps && len(tgt - intersect) < eps) poss++;
		}
	}


	cout <<  poss << endl;

}
