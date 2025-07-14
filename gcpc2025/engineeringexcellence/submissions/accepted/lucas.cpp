#include <bits/stdc++.h>
using namespace std;
using pt = complex<double>;

double dot(pt a, pt b){
	return real(conj(a)*b);
}

double cross(pt a, pt b){
	return imag(conj(a)*b);
}

double sq(double x){
	return x*x;
}

pt rot(pt a){
	return a * pt{0, 1};
}

double solve(pt a, pt b, pt c, pt d, pt e){
	double oldLen = abs(c-b) + abs(c-d);
	double BD = abs(b-d);
	pt bdn = (d-b)/BD;
	pt abn = (b-a)/abs(b-a);
	pt edn = (d-e)/abs(d-e);
	double hdx1 = 1e9, hdx2 = 1e9, l = 0, r = BD;
	if(dot(abn, bdn) > 0){
		hdx1 = 1.0 / dot(abn, bdn) * cross(bdn, abn);
	}
	else{
		pt v = -rot(abn);
		double s = 1.0 / dot(v, bdn) * cross(bdn, v);
		r = BD / (1 + s*s);
	}
	if(dot(edn, -bdn) > 0){
		hdx2 = 1.0 / dot(edn, -bdn) * cross(edn, -bdn);
	}
	else{
		pt v = rot(edn);
		double s = 1.0 / dot(v, -bdn) * cross(v, -bdn);
		l = BD - BD / (1 + s*s);
	}
	auto eval = [&](double x){
		double h1 = hdx1 * x;
		double h2 = hdx2 * (BD-x);
		double h3 = sqrt(sq(BD/2) - sq(BD/2-x));
		double h = min(h3, min(h1, h2));
		return sqrt(sq(h) + sq(x)) + sqrt(sq(h) + sq(BD-x));
	};
	for(int it = 0; it < 100; it++){
		double m1 = (2*l+r)/3, m2 = (l+2*r)/3;
		if(eval(m1) > eval(m2)) r = m2;
		else l = m1;
	}
	double newLen = eval(l);
	return newLen - oldLen;
}

int main(){
	int n;
	cin >> n;
	vector<pt> points;
	for(int i = 0; i < n; i++){
		int x, y;
		cin >> x >> y;
		points.emplace_back(x, y);
	}
	reverse(points.begin(), points.end());
	double ans = 0;
	for(int i = 0; i < n; i++){
		ans = max(ans, solve(points[i], points[(i+1)%n], points[(i+2)%n], points[(i+3)%n], points[(i+4)%n]));
	}
	cout << setprecision(16) << ans << "\n";
}