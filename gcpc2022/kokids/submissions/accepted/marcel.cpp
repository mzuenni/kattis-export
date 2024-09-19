#include<iostream>

using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;

    string br;
    cin >> br;

    int falling = 0;
    if(br[0] == 'R') ++falling;
    
    for(int i = 1; i < n; ++i) {
	if(br[i] == br[i-1]) ++falling;
    }

    cout << max(k - falling, 0) << endl;
}
