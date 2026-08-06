// @EXPECTED_RESULTS@: CORRECT

#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <stack>

using namespace std;

#define MAXM 100000
#define MAXP 4096
#define MAXI 50000000

unsigned char data[MAXM];
char program[MAXP], input[MAXP];
int jump[MAXP];

char * ip;
int memsize, progsize, insize, dataindex, progindex;

inline void wrinc(){ dataindex = (dataindex + 1) % memsize; }
inline void wrdec(){ dataindex = (dataindex + memsize - 1) % memsize; }

inline char getInput(){
	if( ip == input ) return 255;
	return *--ip;
}

void calcJumpPos(){
	stack<int> st;
	memset( jump, -1, sizeof( int ) * progsize );
	for( size_t i = 0; i < progsize; ++i ){
		if( program[i] == '[' )
			st.push(i);
		if( program[i] == ']' ){
			jump[i] = st.top()+1;
			jump[st.top()] = i+1;
			st.pop();
		}
	}	
}

void step(){
	switch( program[progindex++] ){
		case '-' : data[dataindex]--; break;
		case '+' : data[dataindex]++; break;
		case '<' : wrdec(); break;
		case '>' : wrinc(); break;
		case '[' : progindex = (data[dataindex] == 0) ? jump[progindex-1] : progindex; break;
		case ']' : progindex = (data[dataindex] != 0) ? jump[progindex-1] : progindex; break;
		case ',' : data[dataindex] = getInput(); break;
	}
}

int main(){
	int cases, i;
	cin >> cases;
	string line;
	while( cases-- ){
		cin >> memsize >> progsize >> insize;
		progindex = dataindex = 0;
		memset( data, 0, memsize );
		getline( cin, line );
		getline( cin, line );
		memcpy( program, &line[0], progsize );
		getline( cin, line );
		memcpy( input, &line[0], insize );
		ip = input + insize;
		reverse( input, input + insize );
		calcJumpPos();
		for( i = 0; i < MAXI && progindex < progsize; ++i ) step();
		if( i < MAXI )
			cout << "Terminates" << endl;
		else{
			int mini = progindex, maxi = progindex;
			for( i = 0; i < MAXI; ++i ){
				step();
				mini = min( mini, progindex );
				maxi = max( maxi, progindex );
			}
			cout << "Loops " << mini-1 << " " << maxi << endl;
		}
	}
}
