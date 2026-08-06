// @EXPECTED_RESULTS@: CORRECT
#include <iostream>
#include <string.h>
#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include <stack>

#define AA(i,j) (i)*SD+(j)
int SD;

using namespace std;

int *pa;
int *rk;
int ufind(int i) {
	if(pa[i]!=i) pa[i]=ufind(pa[i]);
	return pa[i];
}
int uunion(int a,int b) {
	a=ufind(a);
	b=ufind(b);
	if(a == b) return 0;
	if(rk[a]>rk[b])
		pa[b]=a;
	else
		pa[a]=b;
	if(rk[a]==rk[b]) rk[b]++;
	return 1;
}

int main() {
  int tcc;
  cin >> tcc;
  for (int tc = 0; tc < tcc; tc++) {
    int Am,An,As,Bm,Bn,Bs;
    cin >> Am >> An >> As;
    cin >> Bm >> Bn >> Bs;

    // TODO remove
    int linecount = Am;

    SD = max(As,Bs);

    // plus one dummy state (number 0)
    int n = An+Bn+1;
    int dummy = 0;
    int Astart = 1;
    int Afinal = An;
    int Bstart = An+1;
    int Bfinal = An+Bn;

    int dfa[n*SD];
    for (int f=0; f<n; f++)
    for (int s=0; s<SD; s++) {
        dfa[AA(f,s)] = 0;
    }
    while (Am-->0) {
      int f,s,t;
      cin >> f >> t >> s;
      dfa[AA(f+1,s)] = t+1;
    }
    while (Bm-->0) {
      int f,s,t;
      cin >> f >> t >> s;
      dfa[AA(f+An+1,s)] = t+An+1;
    }
    
    // init union find
    int lpa[n];
    int lrk[n];
    pa = &(lpa[0]);
    rk = &(lrk[0]);

    for(int i=0; i < n; i++) {
		pa[i]=i;
		rk[i]=0;
	}
    
    // HK
    //bool ok = true;
    stack<pair<int,int> > S;
    //if ((Astart == Afinal) ^ (Bstart == Bfinal)) ok = false;
    uunion(Astart,Bstart);
    S.push(pair<int,int>(Astart,Bstart));
    while (!S.empty()) {
        pair<int,int> P = S.top();
        S.pop();
        for (int s = 0; s < SD; s++) {
            int p = dfa[AA(P.first,s)];
            int q = dfa[AA(P.second,s)];
            int pp = ufind(p);
            int qp = ufind(q);
            if (pp != qp) {
                int Af = ufind(Afinal);
                int Bf = ufind(Bfinal);
                //if (((pp == ufind(Af)) ^ (qp == ufind(Bf))) || ((pp == ufind(Bf)) ^ (qp == ufind(Af)))) ok = false;
                uunion(pp,qp);
                S.push(pair<int,int>(p,q));
            }
        }
    }

    bool equal = true;
    int AfinalClass = ufind(Afinal);
    int BfinalClass = ufind(Bfinal);
    for (int v = 0; v < n; v++)
        if (v != Afinal && v != Bfinal && (AfinalClass == ufind(v) || BfinalClass == ufind(v)))
            equal = false;

    if (equal) 
        cout << "eligible";
    else
        cout << "not eligible";
    cout << endl;
  }
  return 0;
}
