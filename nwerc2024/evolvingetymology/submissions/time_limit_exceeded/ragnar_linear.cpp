#include <iostream>
using namespace std;
int main() {
	int n, k;
	cin >> n >> k;
	string name;
	cin >> name;
	int stride = 1;
	for(int i = 0; i < k; ++i) {
		stride *= 2;
		stride -= n * (stride >= n);
	}
	int pos = 0;
	for(int i = 0; i < n; ++i) {
		cout << name[pos];
		pos += stride;
		pos -= n * (pos >= n);
	}
	cout << endl;
}
