#include <bits/stdc++.h>
using namespace std;

#define SIDE   '#'
#define CORNER 'O'

constexpr int W = 80;

int main(){
	int n;
	cin >> n;
	vector<string> grid(100, string(100, '.'));
	grid[2][1] = grid[3][0] = SIDE;
	if(n % 2 == 0) grid[3][1] = CORNER;
	else grid[2][0] = CORNER, n--;
	for(int i = 2; i < W; i += 2){
		grid[2+i][0] = SIDE;
		grid[2+i][1] = CORNER;
		grid[2+i+1][1] = SIDE;
	}
	for(int j = 0; j < W; j += 2){
		grid[1][2+j] = SIDE;
		grid[1][2+j+1] = CORNER;
		grid[0][2+j+1] = SIDE;
	}
	n /= 2;
	int i = 2;
	auto bottom = [&](int s){
		for(int j = s; j <= W; j += 2){
			grid[i][2+j+1] = SIDE;
			grid[i][2+j] = CORNER;
			grid[i+1][2+j] = SIDE;
		}
	};
	do{
		int x = min(n, W);
		bottom(x);
		n -= x;
		i += 2;
	}while(n);
	bottom(0);
	cout << grid.size() << " " << grid[0].size() << "\n";
	for(string s : grid) cout << s << "\n";
}