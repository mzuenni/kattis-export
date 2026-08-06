// @EXPECTED_RESULTS@: CORRECT

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <utility>

using namespace std;
char field[2][1000][1000];
int width, height, moves, count[2], pos;
typedef pair<int,int> pii;
vector<pii> mov;

string results[3] = {"player two wins", "player one wins", "draw"};

void takeTurn(int p){
	while( pos < mov.size() && field[p^1][mov[pos].second][mov[pos].first] == '#' ){
		field[p^1][mov[pos].second][mov[pos].first] = 'X';
		count[p^1]--;
		++pos;
	}
	if( count[p^1] ) ++pos;
}

int simulate(){
	if( count[0] == count[1] && count[0] == 0 ) return 2;
	int p = 0;
	pos = 0;
	while( (pos < mov.size()) && (count[0] != 0) && (count[1] != 0) ){
		takeTurn(p);
		if( p == 0 && count[1] == 0 ){
			takeTurn(p^1);
			break;
		}
		p = p^1;
	}
	return 2 - ( (count[0] > 0) != (count[1] > 0) ) * ( (count[0] != 0) + 2 * (count[1] != 0) );
}

int main(){
	int cases;
	cin >> cases;
	while( cases-- ){
		cin >> width >> height >> moves;
		count[0] = count[1] = 0;
		string line;
		getline( cin, line );
		for( int p = 0; p < 2; ++p ){
			for( int h = height-1; h >= 0; --h ){
				getline( cin, line );
				for( int w = 0; w < width; ++w ){
					field[p][h][w] = line[w];
					count[p] += (line[w] == '#');
				}
			}
		}
		pii tmp;
		mov.clear();
		for( int i = 0; i < moves; ++i ){
			cin >> tmp.first >> tmp.second;
			mov.push_back( tmp );
		}
		cout << results[simulate()] << endl;
	}
}
