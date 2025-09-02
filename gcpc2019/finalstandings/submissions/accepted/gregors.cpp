#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

const int MAX_T = 101;
const int MAX_P = 101;
double s[MAX_T];
double dif[MAX_P];
char sol[MAX_T][MAX_P];

double probTeamBetter(int p, int numSolved, int z)
{
	vector<vector<double>> dp(p+1, vector<double>(p+1,0));
	dp[0][0] = 1;
	for (int i = 1; i <= p; ++i)
	{
		for (int j = 0; j <= p; ++j)
		{
			if (sol[z][i-1] == '-')
				dp[i][j] = dp[i-1][j];
			else if (sol[z][i-1] == 'X')
				dp[i][j] = j ? dp[i-1][j-1] : 0;
			else
			{
				double sd = s[z] * dif[i-1];
				dp[i][j] = (1-sd) * dp[i-1][j] 
					+ (j ? sd*dp[i-1][j-1] : 0);
			}
		}
	}
	double prob = 0;
	for (int i = numSolved+1; i <= p; ++i)
		prob += dp[p][i];
	return prob;
}

int main()
{
	int t,p; cin >> t >> p;
	for (int i = 0; i < t-1; ++i)
		cin >> s[i];
	for (int i = 0; i < p; ++i)
		cin >> dif[i];
	for (int i = 0; i < t-1; ++i)
		for (int j = 0; j < p; ++j)
			cin >> sol[i][j];
	int numSolved = 0;
	for (int i = 0; i < p; ++i)
	{
		char c; cin >> c;
		if (c == 'X') numSolved++;
	}
	double prob = 1;
	for (int i = 0; i < t-1; ++i)
		prob *= (1-probTeamBetter(p,numSolved,i));
	cout << setprecision(10) << prob << endl;
}
