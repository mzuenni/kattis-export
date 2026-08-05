#include <iostream>
#include <map>
#include <string.h>
#include <assert.h>

using namespace std;

int dp[101][101][101]; // [merchant_id][remaining_gold][souvenirs_received];
string merchant_type[128];
int price[128], G, C, N, package_size[128];

int main(){
	memset(dp,-1,sizeof(dp));
	cin >> G >> C >> N;
	for(int i = 0; i < N; i++)
		cin >> merchant_type[i] >> package_size[i] >> price[i];
	dp[0][C][0] = 0;
	int max_souveniers = 0;
	for(int merchant_id = 0; merchant_id < N; merchant_id++)
		for(int remaining_gold = 0; remaining_gold <= C; remaining_gold++)
			for(int souvenirs_received = 0; souvenirs_received <= max_souveniers; souvenirs_received++){
				int silver_coins = dp[merchant_id][remaining_gold][souvenirs_received];
				if(silver_coins >= 0){
					dp[merchant_id + 1][remaining_gold][souvenirs_received] = max(dp[merchant_id + 1][remaining_gold][souvenirs_received], dp[merchant_id][remaining_gold][souvenirs_received]);
//				cout << merchant_id << " " << remaining_gold << " " << souvenirs_received << " " << silver_coins << endl;
					if(remaining_gold > 0 && (merchant_type[merchant_id] != "generous" || silver_coins < price[merchant_id] || G == price[merchant_id])){
						// pay with gold:
						int change;
						if(merchant_type[merchant_id] == "generous") change = ((G - price[merchant_id] + package_size[merchant_id] - 1) / package_size[merchant_id]) * package_size[merchant_id];
						else if(merchant_type[merchant_id] == "greedy") change = ((G - price[merchant_id]) / package_size[merchant_id]) * package_size[merchant_id];
						else if(merchant_type[merchant_id] == "honest") change = ((G - price[merchant_id] + package_size[merchant_id] / 2) / package_size[merchant_id]) * package_size[merchant_id];
						else assert(false);
						dp[merchant_id + 1][remaining_gold-1][souvenirs_received + 1] = max(dp[merchant_id + 1][remaining_gold-1][souvenirs_received + 1], silver_coins + change);
						max_souveniers = max(max_souveniers, souvenirs_received + 1);
					}
					if(silver_coins >= price[merchant_id]){
						dp[merchant_id + 1][remaining_gold][souvenirs_received + 1] = max(dp[merchant_id + 1][remaining_gold][souvenirs_received + 1], silver_coins - price[merchant_id]);
						max_souveniers = max(max_souveniers, souvenirs_received + 1);
					}
				}
			}
	cout << max_souveniers << endl;
}
