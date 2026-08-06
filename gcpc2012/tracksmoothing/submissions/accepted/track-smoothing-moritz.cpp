// @EXPECTED_RESULTS@: CORRECT
#include <iostream>
#include <cmath>

using namespace std;

int cases, r, points, fx, fy, px, py, lx, ly;
double l;

int main(){
	cin >> cases;
	while( cases-- ){
		cin >> r >> points;
		l = 1;
		if( points ){
			l = 0;
			cin >> fx >> fy;
			lx = fx, ly = fy;
			while( --points ){
				cin >> px >> py;
				l += sqrt( (px - lx)*(px - lx) + (py - ly)*(py - ly) );
				lx = px; ly = py;
			}
			l += sqrt( (px - fx)*(px - fx) + (py - fy) * (py - fy) );
			l = ( l - 8.0 * atan(1) * r ) / l;
		}
		if( l < 0 ) cout << "Not possible" << endl;
		else cout << l << endl;
	}
}
