#include <bits/stdc++.h>
using namespace std;

const int N = 33, S = 20000;
const double oo = 1e10;
double dp[N][N][S];

int main() {
	int height, width, radius, stamina;
	cin >> height >> width >> radius >> stamina;
	stamina = min(stamina, 20*height*width);

	vector<string> wall(height);
	for (int i = 0; i < height; i++) {
		cin >> wall[i];
		for (int j = 0; j < width; j++) {
			for (int s = 0; s <= stamina; s++) dp[i][j][s] = oo;
		}
	}
	
	set<tuple<double,int,int,int>> Q;
	for (int i = height-1; i >= 0; i--) {
		for (int j = 0; j < width; j++) {
			if (wall[i][j] != '.') {
				Q.insert(make_tuple(0.0, i, j, stamina-(wall[i][j]-'0')));
				break;
			}
		}
		if (!Q.empty()) break;
	}

	while (!Q.empty()) {
		double dist;
		int i, j, s;
		tie(dist,i,j,s) = *begin(Q);
		Q.erase(begin(Q));
		
		for (int di = -radius; di <= radius; di++) {
			for (int dj = -radius; dj <= radius; dj++) {
				if (di*di + dj*dj > radius*radius) continue;
				int ni = i+di, nj = j+dj;
				if (ni < 0 || ni >= height || nj < 0 || nj >= width) continue;
				if (wall[ni][nj] == '.') continue;
				int ns = s - (wall[ni][nj]-'0');
				if (ns < 0) continue;
				
				double new_dist = dist + hypot(di,dj);
				if (new_dist >= dp[ni][nj][ns]) continue;
				Q.erase(make_tuple(dp[ni][nj][ns],ni,nj,ns));
				dp[ni][nj][ns] = new_dist;
				Q.insert(make_tuple(dp[ni][nj][ns],ni,nj,ns));
			}
		}
	}
	
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (wall[i][j] == '.') continue;

			double res = oo;
			for (int s = 0; s <= stamina; s++) res = min(res, dp[i][j][s]);
			
			if (res < oo) cout << fixed << setprecision(20) << res << endl;
			else cout << "impossible" << endl;
			return 0;
		}
	}
}
