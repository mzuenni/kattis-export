#include<bits/stdc++.h>
using namespace std;

enum strategy {HORIZONTAL, VERTICAL};

pair<int, int> read(){
    int x, y;
    cin >> x >> y;
    return {x, y};
}

void write(int x, int y){
    cout << x << ' ' << y << endl;
}

int main(){
    write(5, 5);

    strategy s;
    auto [x, y] = read();
    if(y != 5) s = HORIZONTAL;
    else s = VERTICAL;

    if(s == HORIZONTAL){
        write(4, 5);
        auto [x, y] = read();
        if(x == 3 && y == 5) write(6, 5);
        else write(3, 5);
    } else{
        write(5, 4);
        auto [x, y] = read();
        if(x == 5 && y == 3) write(5, 6);
        else write(5, 3);
    }
}