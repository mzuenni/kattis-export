// 
// 
#include <list>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cfloat>
#include <climits>
#include <numeric>
#include <iomanip>

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


///////////////////////////////
// BEGIN bignum library v1.0 //
///////////////////////////////
char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
int nums[256];

struct bigint {
	vi d;
	int B;

	bigint():B(10){};
	explicit bigint(int _B):B(_B){};

	bigint& operator=(const bigint &o) {
		B = o.B;
		d = o.d;
		return *this;
	}
	bigint& operator+=(int rhs) { // needs rhs+B < MAXINT, rhs>=0
		if(rhs==0) return *this;
		if(sz(d)==0) d.push_back(0);
		d[0]+=rhs;
		for(int i=0;d[i]>=B;i++) {
			if(i == sz(d)-1) d.push_back(0);
			d[i+1] += d[i]/B;
			d[i]%=B;
		}
		return *this;
	}
	bigint& operator-=(int rhs) { // needs rhs>=0
		if(sz(d)==0) return *this; // already 0
		d[0]-=rhs;
		for(int i=0;d[i]<0;i++) {
			if(i == sz(d)-1) {
				d.clear();
				return *this;
			}
			int mul=(d[i]/B - 1);
			d[i+1] += mul;
			d[i]-=B*mul;
		}
		while(sz(d)>0 && d.back()==0) d.pop_back();
		return *this;
	}
	bigint& operator*=(int rhs) { // needs rhs*B*B/(B-1) < MAXINT
		if(rhs==0)
			d.clear();
		else {
			FOR(i,0,sz(d)) d[i]*=rhs;
			int r=0;
			for(int i=0;i<sz(d) || r>0;i++) {
				if(i == sz(d)) d.push_back(0);
				d[i] += r;
				r = d[i]/B;
				d[i]%=B;
			}
		}
		return *this;
	}
	bigint& operator/=(int q) { // needs q>=0
		int r=0;
		FORD(i,0,sz(d)) {
			int c=d[i]+r*B;
			r = c%q;
			d[i]=c/q;
			if(d.back()==0)d.pop_back();
		}
		return *this;
	}
	bigint& operator=(int rhs) { // needs +=(int)
		d.clear();
		return ((*this) += rhs);
	}
	bigint& toBase(int nB) { // needs +=(int), *=(int)
		int oB=B;
		B=nB;
		vi od;
		od.swap(d);
		FORD(i,0,sz(od)) {
			(*this) *= oB;
			(*this) += od[i];
		}
		return *this;
	}

	bigint& operator+=(const bigint &rhs) { // needs B+B < MAXINT
		if(B != rhs.B) toBase(rhs.B); // change base if necessary
		int r=0;
		for(int i=0;i<sz(rhs.d) || r>0;i++) {
			if(i == sz(d)) d.push_back(0);
			d[i]+=(i<sz(rhs.d) ? rhs.d[i] : 0) + r;
			r = d[i]/B;
			d[i]%=B;
		}
		return *this;
	}
	bigint& operator-=(const bigint &rhs) { // needs *this >= rhs
		if(B != rhs.B) toBase(rhs.B); // change base if necessary
		int r=0;
		for(int i=0;i<sz(rhs.d) || r>0;i++) {
			if(i == sz(d)) {
				d.clear();
				return *this;
			}
			d[i] -= (i<sz(rhs.d) ? rhs.d[i] : 0) + r;
			if((r=(d[i]<0))) d[i]+=B;
		}
		while(sz(d)>0 && d.back()==0) d.pop_back();
		return *this;
	}
	bigint& operator*=(const bigint &rhs) { // needs =(bigint), *=(int), +=(bigint), <<=(int)
		if(B != rhs.B) toBase(rhs.B); // change base if necessary
		bigint tmp(B),tmp2(B);
		FORD(i,0,sz(rhs.d)){
			tmp2 = (*this);
			tmp2*=rhs.d[i];
			tmp<<=1; // faster than tmp*=rhs.B; for same bases
			tmp+=tmp2;
		}
		d.swap(tmp.d);
		return *this;
	}
	bigint& operator/=(const bigint &rhs) {
		DivRem(rhs);
		return *this;
	}
	bigint& operator%=(const bigint &rhs) {
		*this=DivRem(rhs);
		return *this;
	}
	bigint DivRem(const bigint &rhs) { // needs =(bigint), *=(int), -=(bigint), <<=(int)
		if(B != rhs.B) toBase(rhs.B); // change base if necessary
		bigint quo(B);
		int n=sz(rhs.d);
		int m=sz(d)-n;
		FORD(i,0,m+1) {
			int div = min( ((sz(d)<n+i+1 ? 0 : d[n+i])*B + (sz(d)<n+i ? 0 : d[n-1+i])) /rhs.d[n-1] + 1,B); // all +1 for do loop
			bigint tmp(B);
			do {
				div--;
				if(div==0){
					tmp.d.clear();
					break;
				}
				tmp=rhs;
				tmp*=div;
				tmp<<=i;
			}
			while((*this)<tmp);
			*this -= tmp;
			quo.d.push_back(div);
		}
		reverse(all(quo.d));
		while(sz(quo.d)>0 && quo.d.back()==0) quo.d.pop_back();
		d.swap(quo.d);
		return quo;
	}

	bigint& pow(int e) {
		bigint r(B);r = 1;
		while(e) {
			if(e%2) r*=(*this);
			(*this)*=(*this);
			e/=2;
		}
		r.d.swap(d);
		return *this;
	}

	bigint& root(int k){
		bigint u = (*this);
		u >>= ((sz(d)-1)/k)*(k-1); //speedup
		bigint s(B);
		do {
			s = u;
			u*=k-1;
			bigint t2=(*this);
			bigint t3=s;
			t3.pow(k-1);
			t2/=t3;
			u+=t2;
			u/=k;
		}
		while(u<s);
		s.d.swap(d);
		return *this;
	}

	bigint SqrtRem(){
		int l = sz(d)/4;
		if(l == 0) {
			bigint t1 = *this;
			bigint t2 = root(2);
			t2*=t2;
			return (t1-=t2);
		}
		bigint a[4],ss,s,rr,r,q,u;
		FOR(i,0,4) a[i].B=B;
		FOR(i,0,sz(d)) a[min(i/l,3)].d.push_back(d[i]);
		((ss=a[3])<<=l)+=a[2];
		rr = ss.SqrtRem();
		((q=rr)<<=l)+=a[1];
		(a[3]=ss)*=2;
		u = q.DivRem(a[3]);
		((s=ss)<<=l)+=q;
		((r=u)<<=l)+=a[0];
		q*=q;
		while(r<q) {
			((r+=s)+=s)-=1;
			s-=1;
		}
		r-=q;
		s.d.swap(d);
		return r;
	}

	bool operator==(const bigint &o) const {
	    return B==o.B && d==o.d;
	}

	bool operator<(const bigint &o) const { // requires same base
		if(sz(d) != sz(o.d))
			return sz(d)<sz(o.d);
		FORD(i,0,sz(d))
			if(d[i] != o.d[i])
				return d[i]<o.d[i];
		return false;
	}

	string toString() const{
		string ret;
		FORD(i,0,sz(d))
			ret += digits[d[i]];
		if(ret.empty())
			ret="0";
		return ret;
	}
	bigint& fromString(string s) {
		FOR(i,0,B) nums[(int)digits[i]]=i;
		d.clear();
		FORD(i,0,s.length())
			d.push_back(nums[(int)s[i]]);
		while(sz(d)>0 && d.back()==0) d.pop_back();
		return *this;
	}

	bigint& operator<<=(int num){
		if(!d.empty()) d.insert(d.begin(),num,0);
		return *this;
	}
	bigint& operator>>=(int num){
		d.erase(d.begin(),d.begin()+min(num,sz(d)));
		return *this;
	}
};

//////////////////////////
//  END bignum library  //
//////////////////////////


bigint m[2][2];
bigint one;
bigint zero;


void rec(){
	if (m[0][0] == one && m[0][1] == zero && m[1][0] == zero && m[1][1] == one) return;
	// get bits
	int c = 0;
	if (m[0][1] < m[0][0]) FOR(j,0,2) m[j][0] -= m [j][1]; else {
		FOR(j,0,2) m[j][1] -= m [j][0];
		c = 1;
	}
	rec();
	cout << c;
}


int main(){
	one = one.fromString("1");
	zero = zero.fromString("0");
	
	FOR(i,0,2) FOR(j,0,2) {
		string s; cin >> s; m[i][j] = m[i][j].fromString(s);
	}
	rec();
	cout << endl;
}











