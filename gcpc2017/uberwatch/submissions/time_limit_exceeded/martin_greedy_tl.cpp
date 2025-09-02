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
vector<int> A;
array<int, 300000> DP;

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
	cin>>N>>M;
	A.resize(N);
	for(size_t i=0;i<N;i++) cin>>A[i];
	for(size_t i=0;i<N;i++) DP[i] = 0;
	for(size_t i=M;i<N;i++) DP[i] = max(DP[i-1], DP[i-M]+A[i]);
	int sum = 0;
	for(size_t i=0;i<N&&i<M;i++) A[i] = -1;
	while(true)
	{
		auto it = max_element(A.begin(), A.end());
		if(*it == -1) break;
		sum += *it;
		for(auto i=it-(M-1);i!=A.end()&&i!=it+M;i++) *i = -1;
	}
	//cout<<sum<<"\n";
	
	cout << DP[N-1] << "\n";
  return 0;
}

