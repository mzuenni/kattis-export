#include <iostream>
#include <string>
using namespace std;

void output(string s, int pos){
	for(int i=0; i<s.size(); i++){
		if(i == pos) cout << "B";
		else if(i != pos + 1)  cout << s[i];
	}
	cout << endl;
}


int main() {
    string s;
    cin >> s;
    int max_len = 0;
    int position = -1;
    int cur_len = 0;
    for(int i = 0; i < s.size(); i++){
        if(s[i] == 'S'){
            cur_len++;
            if(cur_len > max_len){
                position = i - cur_len + 1;
                max_len = cur_len;

            }
        } else{
            cur_len = 0;
        }
    } 
    output(s, -12);
    if(max_len >= 2) output(s, position);
    if(max_len >= 3) output(s, position+1);
}
