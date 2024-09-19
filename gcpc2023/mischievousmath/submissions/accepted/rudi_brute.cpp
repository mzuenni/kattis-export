#include <bits/stdc++.h>

using namespace std;

int a, b, c, d;
const double eps = 1e-8;

vector<double> combis[101][101];
bool twoCombos[101][101];
vector<double> tmp;

void combine(vector<double> & res, double a, double b){
    res.push_back(a + b);
    res.push_back(a - b);
    res.push_back(a * b);
    res.push_back(a / b);
    res.push_back(b - a);
    res.push_back(b / a);
}

void combineAgain(vector<double> & res, vector<double> v, int x){
    for(double y : v){
        combine(res, y, x);
    }
}

bool containsD(vector<double> v){
    for(double x : v){
        if(abs(x - d) < eps) return true;
    }
    return false;
}


int main(){
    cin >> d;

    for(int i = 1; i <= 100; i++){
        for(int j = 1; j <= 100; j++){
            combine(combis[i][j], i, j);
            twoCombos[i][j] = containsD(combis[i][j]);
        }
    }

    for(a = 1; a<=100;a++){
        if(a == d) continue;
        for(b = a + 1; b < 100; b++){
            if(b == d || twoCombos[a][b]) continue;
            for(c = b + 1; c < 100; c++){
                if(c == d || twoCombos[a][c] || twoCombos[b][c]) continue;

                tmp.clear();
                combineAgain(tmp, combis[a][b], c);
                combineAgain(tmp, combis[b][c], a);
                combineAgain(tmp, combis[a][c], b);
                
                
                if(containsD(tmp)) continue;
                else{
                    cout << a << " " << b << " " << c << endl;
                    return 0;
                }
            }
        }
    }
    cout << "ohje..." << endl;
}

