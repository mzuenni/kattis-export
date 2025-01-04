#include <string>
#include <set>
#include <utility>

using namespace std;

#include "validation.h"

const string ok_chars = "abcdefghijklmnopqrstuvwxyz ";
const auto MAX_LEN = 1'000'000;

int main(int argc, char *argv[]) {
    InputValidator in(argc, argv);
    int n = in.read_integer("n", 1, 100'000);
    in.space();
    int m = in.read_integer("m", 1, 100'000);
    in.space();
    int k = in.read_integer("k", 1, 100'000);
    in.newline();

    int len = 0;
    auto read_string = [&](const string& name) {
        auto s = in.read_line(name, 1, MAX_LEN, ok_chars);
        if(s[0]==' ' || s.back() == ' ') in.WA("leading or trailing space in: '", s, "'");
        len += size(s);
    };

    // read names
    for(int i=0; i<n; ++i) 
        read_string("name" + to_string(i));

    // read rivalries
    set<pair<int,int>> rivs;
    for(int i=0; i<m; ++i) {
        int u = in.read_integer("u", 1, n);
        in.space();
        int v = in.read_integer("v", 1, n);
        in.newline();
        if(u==v) in.WA("self-loop ", u);
        auto [_,inserted] = rivs.insert(minmax(u,v));
        if(!inserted) in.WA("multi-edge ", u, ' ', v);
    }

    // read texts
    for(int i=0; i<k; ++i) 
        read_string("text" + to_string(i));

    if(len<1 || len > MAX_LEN) 
        in.WA("strings too long. summed len of ", len);
}
