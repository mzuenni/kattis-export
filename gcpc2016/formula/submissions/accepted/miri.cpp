#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vl = vector<ll>;
using vvl = vector<vl>;
using pll = pair<ll,ll>;
using vb = vector<bool>;
const ll oo = 0x3f3f3f3f3f3f3f3fLL;
const double eps = 1e-9;
#define sz(c) ll((c).size())
#define all(c) begin(c),end(c)
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define eb emplace_back
#define xx first
#define yy second
#define has(c,i) ((c).find(i) != end(c))
#define FOR(i,a,b) for (int i=(a); i<(b); i++)       
#define FORD(i,a,b) for (int i=int(b)-1; i>=(a); i--)
#define DBGDO(X) ({ if(1) cerr << "DBGDO: " << (#X) << " = " << (X) << endl; })

int main() { 
	ios::sync_with_stdio(false); 
	double x[3], y[3];
	cin >> x[0] >> y[0] >> x[1] >> y[1] >> x[2] >> y[2];
	double r;
	cin >> r;
	double a = sqrt((x[0]-x[1])*(x[0]-x[1]) + (y[0]-y[1]) * (y[0] - y[1]));
	double b = sqrt((x[1]-x[2])*(x[1]-x[2]) + (y[1]-y[2]) * (y[1] - y[2]));
	double c = sqrt((x[0]-x[2])*(x[0]-x[2]) + (y[0]-y[2]) * (y[0] - y[2]));
	double A = a*a + b*b - c*c; A *= A; 
				 A = sqrt(4*a*a*b*b - A)/4.0;
	double rr = A / ((a+b+c)/2.0);
	cout << (rr - r)/r * 100 << endl;
}
