#include <bits/stdc++.h>
using namespace std;

void h(string &s) {
    reverse(begin(s), end(s));
    for (char &c: s) {
        switch(c) {
            case 'b': c = 'd'; break;
            case 'd': c = 'b'; break;
            case 'p': c = 'q'; break;
            case 'q': c = 'p'; break;
        }
    }
}

void v(string &s) {
    for (char &c: s) {
        switch(c) {
            case 'b': c = 'p'; break;
            case 'd': c = 'q'; break;
            case 'p': c = 'b'; break;
            case 'q': c = 'd'; break;
        }
    }
}

void r(string &s) {
    reverse(begin(s), end(s));
    for (char &c: s) {
        switch(c) {
            case 'b': c = 'q'; break;
            case 'd': c = 'p'; break;
            case 'p': c = 'd'; break;
            case 'q': c = 'b'; break;
        }
    }
}

int main() {
    string s, t;
    cin >> s >> t;

    for (char &c: t) {
        switch(c) {
            case 'h': h(s); break;
            case 'v': v(s); break;
            case 'r': r(s); break;
        }
    }

    cout << s << '\n';
}
