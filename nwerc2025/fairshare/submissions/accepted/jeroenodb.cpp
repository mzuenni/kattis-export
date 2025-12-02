#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n; 
    cin >> n;
    long long total = 0;
    vector<int> a(n),b(n);
    for(int i=0;i<n;++i) {
        cin >> a[i] >> b[i];
        total+=b[i]-a[i];
    }
    for(int i=0;i<n;++i) {
        if(total+a[i]<=b[i]) {
            cout << i+1 << '\n';
            exit(0);
        }
    }
    cout << "impossible\n";
}