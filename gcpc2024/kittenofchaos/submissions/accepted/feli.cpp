#include<bits/stdc++.h>

using namespace std;

bool flip(bool b){
	if(b) b = false;
	else b = true;
	return b;
}

int main(){
	string s;
	cin >> s;
	string o;
	cin >> o;
	bool h = false;
	bool v = false;
	for(char c:o){
		if( c == 'h')
			h = flip(h);
		else if(c == 'v')
			v = flip(v);
		else{
			h = flip(h);
			v = flip(v);
		}
	}
	if(h){
		reverse(s.begin(), s.end());
		string sol;
		for (char c:s){
			if(c == 'b')
				sol += 'd';
			if(c == 'p')
				sol += 'q';
			if(c == 'q')
				sol += 'p';
			if(c == 'd')
				sol += 'b';
		}
		s= sol;
	}
	if(v){
		string sol;
		for (char c:s){
			if(c == 'b')
				sol += 'p';
			if(c == 'p')
				sol += 'b';
			if(c == 'q')
				sol += 'd';
			if(c == 'd')
				sol += 'q';
		}
		s = sol;
	}
	cout << s << endl;
}
