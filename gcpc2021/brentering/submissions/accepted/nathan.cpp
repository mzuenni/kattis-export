#include<bits/stdc++.h>
using namespace std;
set<char> v = {'a', 'e', 'i', 'o', 'u'};

int main() {
    string s;
    cin >> s;
    while (!v.count(s.back())) s.pop_back();
    cout << s << "ntry" << endl;
    return 0;
}

