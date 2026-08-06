// @EXPECTED_RESULTS@: WRONG-ANSWER

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>
#include <utility>

#define MAXN 10000

using namespace std;
bool set[MAXN];
char reconstructed[MAXN+1];
int cases, lines, length, ind;
string suffix;
vector< pair< int, string > > input_data;

bool check( int i, int j, int pos ){
	if( set[pos] && reconstructed[pos] != input_data[i].second[j] ){
		cout << "IMPOSSIBLE" << endl;
		return false;
	}
	set[pos] = true;
	reconstructed[pos] = input_data[i].second[j];
	return true;
}

void solve(){
	reconstructed[length] = '\0';
	set[length] = true;
	for( size_t i = 0; i < input_data.size(); ++i ){
		size_t j;
		for( j = 0; j < input_data[i].second.length() && input_data[i].second[j] != '*'; ++j )
			if( !check( i, j, input_data[i].first + j ) )
				return;
		if( j < input_data[i].second.length() ){
			for( j = 0; j < input_data[i].second.size() && input_data[i].second[input_data[i].second.size() - 1 - j] != '*'; ++j )
				if( !check( i, input_data[i].second.size() - j - 1, length - j - 1 ) )
					return;
		}
	}
	for( size_t i = 0; i < length; ++i ){
		if( !set[i] ){
			cout << "IMPOSSIBLE" << endl;
			return;
		}
	}
	cout << reconstructed << endl;
}


int main(){
	cin >> cases;
	while( cases-- ){
		input_data.clear();
		cin >> length >> lines;
		while( lines-- ){
			cin >> ind;
			--ind;
			cin.ignore();	//skip whitespace
			getline( cin, suffix );
			input_data.push_back( make_pair( ind, suffix ) );
		}
		solve();
	}
	return 0;
}
