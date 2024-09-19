#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll,ll> pll;

int main(){
	ll n;
	cin >> n;
	vector<pll> intervals;
	for(int i = 0; i< n; i++){
		ll a, b;
		cin >> a >> b;
		intervals.push_back(make_pair(a,b));
	}
	sort(intervals.begin(), intervals.end());
	vector<vector<pll> > comps;
	vector<pll> tmp;
	tmp.push_back(intervals[0]);
	for(int i = 1; i< n; i++){
		if(intervals[i-1].second < intervals[i].first){
			comps.push_back(tmp);
			tmp.clear();
		}
		tmp.push_back(intervals[i]);
	}
	comps.push_back(tmp);
	ll res = 4;
	for(int z = 0; z< comps.size(); z++){
		intervals.clear();
		intervals = comps[z];
		//for(int i = 0; i< intervals.size(); i++){
	//		cout <<"(" << intervals[i].first << ", " << intervals[i].second << ") ";
	//	}
	//	cout << endl;
	//	cout << "input" <<endl;
		vector<ll> pred;//pred ist das Intervall mit dem kleinsten Startpunkt, dessen Ende noch in i liegt
		pred.push_back(-1);
		for(int i = 1; i < intervals.size(); i++){
			//cout << "schleifepred"<< endl;
			if(intervals[i-1].second < intervals[i].first){
				pred.push_back(-1);
			}
			else if(i> 1 && intervals[pred[i-1]].second >= intervals[i].first){
				pred.push_back( pred[i-1]);
			}
			else{
				for(int k = pred[i-1]+1; k < i; k++){
					if(intervals[k].second >= intervals[i].first){
						pred.push_back(k);
						break;
					}
				}
			}
		}
		//cout << "pred" << endl;
		vector<ll> lastend; // lastend ist das Intervall mit dem groessten Startpunkt, dessen Ende vor i liegt
		lastend.resize(intervals.size());
		for(int i = intervals.size()-1; i >=0; i--){
			if(i+1 <intervals.size() && intervals[lastend[i+1]].second < intervals[i].first){
				lastend[i] = lastend[i+1];
			}
			else{
				ll k;
				if(i==intervals.size()-1) k = intervals.size()-1;
				else k = lastend[i+1]-1;
				for(; k >= 0; k--){
					if(intervals[k].second < intervals[i].first){
						lastend[i] = k;
						break;
					}
				}
				if(k == -1){
					while(i>=0){
						lastend[i] = -1;
						i--;
					}
				}

			
			}
		}
	//	cout << lastend[0] << " " <<  pred[0] << endl;
		//cout << "lastend" << endl;
		ll dp[n][4];
		for(int k = 0; k < 4; k++){
			for(int i =0; i < intervals.size(); i++){
				if(i == 0 || lastend[pred[i]] == -1)
					dp[i][k] = 1;
				else{
					dp[i][k] = dp[lastend[pred[i]]][k] +1;
					ll p = pred[i];
					for(int l = 0; l < k; l++){
						p = pred[p];
						if(lastend[p] == -1){ 
							dp[i][k] = 1;
							break;
						}
						dp[i][k] = min(dp[i][k], dp[lastend[p]][k-l]+1);
					}
				}
			}
		}
	//	cout << "dp" << endl;
	//	cout << z << ": " << dp[intervals.size()-1][0] << " -> ";
		ll i;
		for(i = 1; i < 4; i++){
		//	cout << dp[intervals.size()-1][i] << " ";
			if(dp[intervals.size()-1][i] < dp[intervals.size()-1][0]){
				res = min(res, i);
				break;
			}
		}
	//	cout << endl;
	}
	if(res < 4){
		cout << res << endl;
	}
	else{
		cout << "impossible" << endl;
	}
}
