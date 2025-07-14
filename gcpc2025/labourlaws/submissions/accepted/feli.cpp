#include<bits/stdc++.h>

using namespace std;

int main(){
	int t;
	cin >> t;
	if (t <= 360){
		cout << "0" << endl;
	}
	else if(t <= 390){
		cout << t-360 << endl;
	}
	else if(t <= 570){
		cout << "30" << endl;
	}
	else if(t <= 585){
		cout << t-540 << endl;
	}
	else if(t <= 645){
		cout << "45" << endl;
	}
	else{
		cout << t-600 << endl;
	}

}
