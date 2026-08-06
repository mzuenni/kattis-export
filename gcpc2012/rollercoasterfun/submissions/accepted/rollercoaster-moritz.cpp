// @EXPECTED_RESULTS@: CORRECT
#include <iostream>
#include <algorithm>

using namespace std;

int fun[50000+1], ncoast, max_time, coasters[100+1][3], quer, cur, funi;

void calc(){
	for( int c = 0; c < ncoast; ++c ){
		if( !coasters[c][1] ){
			for( int j = coasters[c][2]; j <= max_time ; ++j ) 	fun[j] = max( fun[j], fun[j - coasters[c][2]] + coasters[c][0] );
		} else {
			for( int t = 0; coasters[c][0] >= t * t * coasters[c][1]; ++t )
				for( int j = max_time; j >= coasters[c][2]; --j )
					fun[j] = max( fun[j], fun[j - coasters[c][2]] + coasters[c][0] - t * t * coasters[c][1] );
		}
	}
}

int main(){
	cin >> ncoast;
	max_time = 25000;
	for( int i = 0; i < ncoast; ++i ) cin >> coasters[i][0] >> coasters[i][1] >> coasters[i][2];
	calc();
	cin >> quer;
	while( quer-- && (cin >> max_time) ) cout << fun[max_time] << "\n";
}
