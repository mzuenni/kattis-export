#include <string>
#include <iostream>

using namespace std;

int main() {
	string proportion;
	cin >> proportion;
	if(proportion[0] != '0')return -1;
	if(proportion[1] != '.')return -2;
	for(unsigned int i = 2; i < proportion.size(); i++){
		if(proportion[i] < '0' || proportion[i] > '9')return -3;
	}
	if(proportion.size() > 7 + 2)return -4;
	return 42;
}
