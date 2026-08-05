#include <bits/stdc++.h>
using namespace std;

typedef array<double,3> vec;
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
const double eps = 1e-6;

vec operator+(const vec &a, const vec &b) { return {a[0]+b[0], a[1]+b[1], a[2]+b[2]}; }
vec operator-(const vec &a, const vec &b) { return {a[0]-b[0], a[1]-b[1], a[2]-b[2]}; }
vec operator*(const double &t, const vec &a) { return {t*a[0], t*a[1], t*a[2]}; }

double operator*(const vec &a, const vec &b) {
	double sum;
	FOR(i,0,3) sum += a[i]*b[i];
	return sum;
}

vec operator^(const vec &a, const vec &b) {
	vec c;
	FOR(i,0,3) c[i] = a[(i+1)%3]*b[(i+2)%3] - a[(i+2)%3]*b[(i+1)%3];
	return c;
}

double norm(const vec &a) { return sqrt(a * a); }

istream &operator>>(istream &in, vec &a) { FOR(i,0,3) in >> a[i]; return in; }

int main() {
	int n;
	double d;
	vec p1, p2, normal;
	cin >> n >> d >> p1 >> p2;
	normal = p1 ^ p2;
	int res = 0;
	FOR(i,0,n) {
		vec s, t; 
		cin >> s >> t;
		vec v = s - d*t;
		res += abs(norm(v) - d) < eps && abs(v * normal) < eps;
	}
	cout << res << endl;
}

