
#include <list>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cfloat>
#include <numeric>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<string> vs;
typedef pair<int, int> pii;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;

#define sz(c) int((c).size())
#define all(c) (c).begin(), (c).end()
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define FORD(i,a,b) for (int i = int(b)-1; i >= (a); i--)
#define FORIT(i,c) for (__typeof__((c).begin()) i = (c).begin(); i != (c).end(); i++)
#define mp(a,b) make_pair(a,b)
#define pb(a) push_back(a)

int MAXN = 100, MAXT = 25000, MAXQ = 1000;
int primes[1000],P;
void genWorstCaseOfAc(){
	cout << MAXN << endl;
	FOR(i,0,MAXN){
		cout << "1000 1 1" << endl;
	}
	cout << MAXQ << endl;
	cout << MAXT << endl;
	FOR(i,1,MAXQ)cout << abs(rand()%MAXT) << endl;
}
void genCaseMuchUpdate(){
	cout << MAXN << endl;
	FOR(i,0,MAXN){
		cout << (i+1) * 10 << " 0 1\n";
	}
	cout << MAXQ << endl;
	cout << MAXT << endl;
	FOR(i,1,MAXQ)cout << abs(rand()%MAXT) << endl;
}
void genCaseMuchUpdate2(){
	cout << MAXN << endl;
	FOR(i,0,MAXN){
		int cp = primes[MAXN-i-1];
		cout << cp -1 << " 0 " << cp << endl;
	}
	cout << MAXQ << endl;
	cout << MAXT << endl;
	FOR(i,1,MAXQ)cout << abs(rand()%MAXT) << endl;
}

void genCaseWithPrimesRandom(){
	cout << MAXN << endl;
	FOR(i,0,MAXN){
		cout << 1+(rand()%1000) <<  " " << rand()%1000 << " "<< primes[P-i-1] << endl;
	}
	cout << MAXQ << endl;
	cout << MAXT << endl;
	FOR(i,1,MAXQ)cout << abs(rand()%MAXT) << endl;
}

void genZeroTestCase(){
	cout << MAXN << endl;
	FOR(i,0,MAXN){
		cout << 0 << " " << abs(rand()%3) <<  " "<< primes[i] << endl;
	}
	cout << MAXQ << endl;
	int q1 = MAXQ / 3;
	FOR(i,0,q1)cout << i << endl << MAXT - i << endl;
	FOR(i,2*q1,MAXQ)cout << (abs(rand()% MAXT)) << endl;
}
int srandValues[5] = {81236421, 54054, 47474091, 78348257, 2028494064};
void genRandom(){
	int id;
	int N;
	cin >> id >> N;
	N = min(N, MAXN);
	srand(srandValues[id]);
	cout << N  << endl;
	FOR(i,0,N)cout << abs(rand() % 1000) << " "<< abs(rand() % 3) << " "<< 1+abs(rand() % 50) << endl;
	cout << MAXQ << endl;
	int RQ = MAXQ;
	int q1 = MAXQ / 3;
	FOR(i,0,q1)cout << MAXT - i << endl << i << endl;
	RQ -= 2* q1;
	while(RQ--)cout << abs(rand()%MAXT) << endl;
}
int main() {
	P = 0;
	FOR(i,2,1000){
		bool ispr = 1;
		FOR(j,2,i)if(i%j==0)ispr = 0;
		if(ispr)primes[P++]=i;
	}
//	genWorstCaseOfAc();
//	genCaseMuchUpdate();
//	genCaseMuchUpdate2();
//	genCaseWithPrimesRandom();
//	genZeroTestCase();
	genRandom();
	return 0;
}
