#include <list>
#include <map>
#include <stack>
#include <queue>
#include <set>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cfloat>
#include <numeric>
#include <iomanip>
#include <cassert>
#include <unordered_set>
#include <unordered_map>
#include <bitset>
#include <tuple>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<string> vs;
typedef pair<int,int> pii;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;

#define sz(c) int((c).size())
#define all(c) (c).begin(), (c).end()
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define FORD(i,a,b) for (int i = int(b)-1; i >= (a); i--)
#define FORIT(i,c) for (auto i=(c).begin(); i!=(c).end(); i++)
#define mp make_pair
#define pb push_back
#define has(c,i) ((c).find(i) != (c).end())
#define DBG(...) ({ if(1) fprintf(stderr, __VA_ARGS__); })
#define DBGDO(X) ({ if(1) cerr << "DBGDO: " << (#X) << " = " << (X) << endl; })

struct ENTRY {
	int todo, vMin, vMax;

	ENTRY(): todo(0), vMin(0), vMax(0) {}

};

struct SegTree {
	vector<ENTRY> node;
	int maxIdx, N;
	
	SegTree(int mi, int n) : maxIdx(mi), N(n) {
		node.resize(maxIdx * 4 + 1);  
	}  
	
	pii aio(int a, int b, int v = 0, int p = 0, int i = 0, int j = -1) {    
		if (j == -1) j = maxIdx;  
		if (b < i || j < a) return mp(N+1,-1); 
		if (a <= i && j <= b) { 
			node[p].todo += v;
			return mp(node[p].vMin+node[p].todo,node[p].vMax+node[p].todo);
		}
		   
		int p1 = 2*p+1; 
		int p2 = 2*p+2; 
		node[p1].todo += node[p].todo;
		node[p2].todo += node[p].todo;
		node[p].todo = 0;
		
		pii ret1 = aio(a, b, v, p1, i,   (i+j)/2);
		pii ret2 = aio(a, b, v, p2, (i+j)/2+1, j);
		
		node[p].vMin = min(ret1.first, ret2.first)+node[p].todo;
		node[p].vMax = max(ret1.second, ret2.second)+node[p].todo;

		return mp(node[p].vMin, node[p].vMax);
	}

	int change(int from, int to, int diff) {
		pii range = aio(from, to);
		if (diff > 0) {
			diff = min(diff, N-range.second);
		} else {
			diff = max(diff, -range.first);
		}
		aio(from, to, diff);		
		return diff;
	}

};

int main() { 
	ios_base::sync_with_stdio(false); 
	
	int C, N,  O;
	cin >> C >> N >> O;
	
	SegTree sg(C, N);

	FOR(i,0,O) {
		string cur;
		int from, to, diff;
		cin >> cur;
		switch(cur[0]) {
		case 's':
			cin >> from;
			cout << sg.aio(from,from).first << endl;
			break;
		case 'c':
			cin >> from >> diff;
			cout << sg.change(from, from, diff) << endl;
			break;
		case 'g':
			cin >> from >> to >> diff;
			cout << sg.change(from, to, diff) << endl;
			break;
		}
	}
}

