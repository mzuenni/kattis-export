#include <bits/stdc++.h>
using namespace std;

int profile[20000];
int main()
{
    int n, tmp, len = 0;
    memset(profile, 0, sizeof(profile));
    for(int i=0; i<5; i++){
        cout << "? ";
        for(int c = 0; c < 26; c++) if((c+1) & (1 << i)) cout << char('a' + c);
        cout << endl << flush;
        cin >> n;
        for(int j=0; j<n; j++) {
            cin >> tmp;
            len = max(len, tmp);
            profile[tmp - 1] += (1 << i);
        }
    }
    cout << "! ";
    for(int i=0; i<len; i++) cout  <<  char('a' + (profile[i] - 1));
    cout << endl << flush;
}
