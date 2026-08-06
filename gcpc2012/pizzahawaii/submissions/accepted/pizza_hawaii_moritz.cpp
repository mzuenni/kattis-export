// @EXPECTED_RESULTS@: CORRECT
#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <string>
#include <utility>
#include <vector>

using namespace std;

map<string,unsigned long long > pmap[2];
typedef pair<string,string> pss;
typedef pair<unsigned long long, string> pis;
vector< pis > idlist[2];
vector< pss > results;

int comp( const pis & a, const pis & b ){ return a.first < b.first; }

int main(){
	int npizza, icount;
	string str;
	bool first = true;

	cin >> npizza; // skip number of testcases
	while( cin >> npizza ){
		if( !first )
			cout << "\n";
		first = false;
		pmap[0].clear();
		pmap[1].clear();
		for( int p = 0; p < npizza; ++p ){
			cin >> str;	//skip name;
			for( int l = 0; l < 2; ++l ){
				cin >> icount;
				for( int i = 0; i < icount; ++i ){
					cin >> str;
					pmap[l][str] |= (1llu << p);
				}
			}
		}
		for( int l = 0; l < 2; ++l ){
			idlist[l].clear();
			for( map<string,unsigned long long>::iterator itr = pmap[l].begin(), end = pmap[l].end(); itr != end; ++itr ){
				idlist[l].push_back( pis( itr->second, itr->first ) );
			}
			sort( idlist[l].begin(), idlist[l].end() );
		}
		results.clear();
		for( int i = 0; i < idlist[0].size(); ++i ){
			int beg = lower_bound( idlist[1].begin(), idlist[1].end(), idlist[0][i], comp )-idlist[1].begin(), end = upper_bound( idlist[1].begin(), idlist[1].end(), idlist[0][i], comp )-idlist[1].begin();
			for( int j = beg; j < end; ++j )
				results.push_back( pss( idlist[0][i].second, idlist[1][j].second ) );
		}
		sort( results.begin(), results.end() );
		for( size_t i = 0; i < results.size(); ++i ){
			cout << "(" << results[i].first << ", " << results[i].second << ")\n";
		}
	}
}
