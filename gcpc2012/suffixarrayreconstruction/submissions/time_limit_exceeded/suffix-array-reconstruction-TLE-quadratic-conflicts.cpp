// @EXPECTED_RESULTS@: TIMELIMIT

#include <algorithm>
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
vector< pair< int, string > > prefix;
vector< string > suffix;

int compp( const pair<int,string> & a, const pair<int,string> & b ){
	if( a.first == b.first )
		return a.second.length() > b.second.length();
	return a.first < b.first;
}

int comp( const string & a, const string & b ){
	return a.length() < b.length();
}

bool do_conflict( int ab, const string & a, int bb, const string & b ){
	int i = 0;
	while( ab + i < a.length() && bb + i < b.length() ){
		if( a[ab+i] != b[bb+i] ){
			return true;
		}
		++i;
	}
	return false;
}

void solve(){
	memset( set, false, sizeof(bool) * length );
	memset( reconstructed, ' ', sizeof(char) * length);
	reconstructed[length] = '\0';

	sort( prefix.begin(), prefix.end(), compp );
	sort( suffix.begin(), suffix.end(), comp );

	bool conflict = false;
	for( size_t i = 0; i < prefix.size() && !conflict; ++i ){
		for( size_t j = i + 1; j < prefix.size() && !conflict; ++j ){
			int first = max( prefix[i].first, prefix[j].first );
			conflict = do_conflict( first - prefix[i].first, prefix[i].second, first - prefix[j].first, prefix[j].second );
		}
	}

	for( size_t i = 0; i < suffix.size() && !conflict; ++i ){
		for( size_t j = i + 1; j < suffix.size() && !conflict; ++j ){
			int first = min( suffix[i].length(), suffix[j].length() );
			conflict = do_conflict( suffix[i].length() - first, suffix[i], suffix[j].length() - first, suffix[j] );
		}
	}

	for( size_t i = 0; i < prefix.size() && !conflict; ++i ){
		for( size_t j = 0; j < suffix.size() && !conflict; ++j ){
			int first = max( prefix[i].first, (int)(length - suffix[j].length()) );
			conflict = do_conflict( first - prefix[i].first, prefix[i].second, suffix[j].length() - (length - first), suffix[j] );
		}
	}

	if( conflict ){
		cout << "IMPOSSIBLE" << endl;
		return;
	}

	for( size_t i = 0; i < suffix[suffix.size()-1].length(); ++i ){
		reconstructed[length-suffix[suffix.size()-1].length()+i] = suffix[suffix.size()-1][i];
		set[ length-suffix[suffix.size()-1 ].length() + i ] = true;
	}

	int best = 0;
	for( size_t i = 0; i < prefix.size() && !set[best]; ++i ){
		for( size_t j = best - prefix[i].first; j < prefix[i].second.size() && !set[best]; ++j, ++best ){
			reconstructed[prefix[i].first + j] = prefix[i].second[j];
			set[prefix[i].first + j] = true;
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
	string in_suffix, in_prefix, line;
	cin >> cases;
	while( cases-- ){
		prefix.clear();
		suffix.clear();
		cin >> length >> lines;
		while( lines-- ){
			cin >> ind;
			--ind;
			cin.ignore();	//skip whitespace
			getline( cin, line );
			istringstream iss( line );
			getline( iss, in_prefix, '*' );
			getline( iss, in_suffix );
			prefix.push_back( make_pair( ind, in_prefix ) );
			suffix.push_back( in_suffix );
		}
		solve();
	}
	return 0;
}
