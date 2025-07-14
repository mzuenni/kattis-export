#include <bits/stdc++.h>
using namespace std;

int main(){
	int t;
	cin >> t;
	if(t <= 6*60) cout << "0\n";
	else if(t <= 6*60+30) cout << t-6*60 << "\n";
	else if(t <= 9*60+30) cout << 30 << "\n";
	else if(t <= 9*60+45) cout << t-9*60 << "\n";
	else if(t <= 10*60+45) cout << 45 << "\n";
	else cout << t-10*60 << "\n";
}