#include<bits/stdc++.h>
using namespace std;

string field[100];
const int LEFT = -1;
const int RIGHT = 1;
const int UP = 1;
const int DOWN = -1;

void place(int i, int j, int hor, int ver){
    i = 99 - i;
    field[i][j] = 'O';
    field[i - ver][j] = '#';
    field[i][j + hor] = '#';
}

int main(){
    int a;
    cin >> a;

    cout << "100 100" << endl;
    for(int i=0; i<100; i++){
        field[i] = string(100, '.');
    }

    bool odd = a % 2 == 1;
    if(odd) a += 1;
    int full_rows = a / 96;
    int rem = a % 96;


    for(int j=0; j<100; j+=2) place(1, j, RIGHT, DOWN); // bottom wall
    for(int i=2; i<100; i+=2) place(i, 1, (i == 2 && odd) ? RIGHT : LEFT, UP); // left wall
    for(int i=2; i<100; i+=2) place(i, 98, RIGHT, UP); // right wall

    // top wall
    if(rem == 0){
        for(int j=2; j<98; j+=2) place(2 + full_rows, j, RIGHT, UP);
    } else{
        for(int j=2; j< 2+rem; j+=2) place(3 + full_rows, j, RIGHT, UP);
        for(int j = 2+rem; j < 98; j+=2) place(2 + full_rows, j, RIGHT, UP);
    }
    
    for(int i=0; i<100; i++) cout << field[i] << endl;
}