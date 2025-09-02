#include <bits/stdc++.h>

using namespace std;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const double PI = 2.0 * acos(0.0);


typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<string> vs;

#define sz(c) int((c).size())
#define all(c) (c).begin(), (c).end()
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define FORS(i,a,b,s) for (int i = (a); i < (b); i=i+(s))
#define FORD(i,a,b) for (int i = int(b)-1; i >= (a); i--)
#define FORIT(i,c) for (__typeof__((c).begin()) i = (c).begin(); i != (c).end(); i++)

int v[1000][1000];
int b[1000];

int main(){
	int w,p; cin >> w >> p;
	FOR(i,0,w) FOR(j,0,p) cin >> v[i][j];
	FOR(i,0,w) sort(v[i] + 1, v[i] + p);
	FOR(i,0,w) reverse(v[i] + 1, v[i] + p);

	FOR(i,0,w){
		int bribe = 0;
		int numeq = 1;
		int valeq = v[i][1];

		while (v[i][0] + bribe <= valeq){
			int maxBribe = numeq * ((numeq + 1 < p) ? (valeq - v[i][numeq+1]) : valeq); // don't bribe more than resulting in a tie with the next party.

			int suffBribe = (((- v[i][0] - bribe + valeq)*numeq) / (numeq + 1)) + 1;
			if ((suffBribe % numeq) && suffBribe + v[i][0] + bribe == valeq) suffBribe++;
			if (suffBribe <= maxBribe){
				bribe += suffBribe;
				break; // bribing done
			}

			// perform this bribe
			bribe += maxBribe;
			valeq -= maxBribe / numeq;
			numeq ++;
		}
		b[i] = bribe;
	}
	sort(b, b + w);
	int bb = 0;
	FOR(i,0,w/2 + 1) bb += b[i];
	cout << bb << endl;
}
