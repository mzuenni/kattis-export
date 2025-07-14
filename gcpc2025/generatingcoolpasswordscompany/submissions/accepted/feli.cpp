#include<bits/stdc++.h>

using namespace std;

int main(){
	int n;
	cin >> n;
	int count = 0;
	for(int i = 0; i <9; i++){
		for(char j = 'A'; j <= 'Z'; j++){
			for(char k = 'a'; k <= 'z'; k++){
				if(count == n){
					return 0;
				}
				count++;
				cout << "!." << i << i << j << j << k << k << endl;
			}
		}	
	}
}
