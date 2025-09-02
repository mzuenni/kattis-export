#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>
#include <sstream>
#include <stack>
#include <queue>
#include <map>
#include <climits>
#include <cstdio>
#include <set>
#include <array>
#include <unordered_map>
#include <unordered_set>
#include <iomanip>
#include <functional>
using namespace std;
#define db(a) (cout << (#a) << " = " << (a) << endl)
typedef long long ll;

size_t N,M;
array<int, 300000> A;

int foo(size_t i, int sum)
{
	if(i>=N) return sum;
	int a = foo(i+1, sum);
	int b = foo(i+M, sum+A[i]);
	return max(a,b);
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
	cin>>N>>M;
	for(size_t i=0;i<N;i++) cin>>A[i];
	cout<<foo(M, 0)<<"\n";
  return 0;
}

