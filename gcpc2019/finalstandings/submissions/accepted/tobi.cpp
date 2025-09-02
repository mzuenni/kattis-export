#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;
double S[100], D[100];
int t, p;
string s;
double probs[100][100];
double solved[105][105];

int main() {
	cin >> t >> p;
	for (int i = 0; i < t-1; i++) cin >> S[i];
	for (int i = 0; i < p; i++) cin >> D[i];
	for (int i = 0; i < t; i++) for (int j = 0; j < p; j++) {
		cin >> s;
		if (s[0] == '?') probs[i][j] = S[i]*D[j];
		else probs[i][j] = s[0] == 'X';
	}
	double winner = 1.;
	int toBeat = 0;
	for (int i = 0; i < p; i++) toBeat += (probs[t-1][i] == 1);
	for (int i = 0; i < t - 1; i++) {
		solved[i][0] = 1.;
		for (int j = 0; j < p; j++) {
			for (int k = p; k >= 0; k--) {
				solved[i][k] *= (1-probs[i][j]);
				if (k > 0) solved[i][k] += solved[i][k-1]*probs[i][j];
			}
		}
		double more = 0;
		for (int j = toBeat + 1; j <= p; j++) more += solved[i][j];
		winner *= (1. - more);
	}
	cout << setprecision(12) << winner << endl;

	return 0;
}
