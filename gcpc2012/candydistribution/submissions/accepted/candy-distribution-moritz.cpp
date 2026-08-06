// @EXPECTED_RESULTS@: CORRECT

#include <iostream>
#include <algorithm>
#include <utility>

using namespace std;

typedef pair<long long, long long> pll;

pair< long long, pll > extendedEuklid( long long a, long long b ){
	if( b == 0 )
		return make_pair( a, make_pair( 1ll, 0ll) );
	pair< long long, pll > p = extendedEuklid( b, a % b );
	return make_pair( p.first, make_pair( p.second.second, p.second.first - a / b * p.second.second ) );
}

int main(){
	int cases;
	cin >> cases;
	while( cases-- ){
		long long kids, bagsize;
		cin >> kids >> bagsize;
		if( bagsize == 1 ) { cout << kids+1 << endl; continue; }
		if( kids == 1 ){ cout << "1" << endl; continue; }
		pair< long long, pll > p = extendedEuklid( bagsize, kids );
		int d = p.first, y = p.second.first;
		if( (1 % d) != 0 ){
			cout << "IMPOSSIBLE" << endl;
		} else {
			cout << (p.second.first + kids) % kids << endl;
		}
	}
}
