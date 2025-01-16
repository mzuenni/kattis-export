#include<vector>
#include<iostream>

using namespace std;

const int MAXN = 200000;

int tmp[7];
int daysize[7];

int guesses[MAXN][7];

int pascal[7];
int n;


pair<int, int> transl(int day, int guess){
    int erg = 0;
    for(int d = 0; d < day; d++) erg += daysize[d];
    if(guess < 0) return {erg - guess - 1, false};
    else return {erg + guess - 1, true};
}

void terminate(bool erg){
    if(erg) cout << "inpossible" << endl;
    else cout << "impossible" << endl;
    exit(0);
}

bool exists_guess(int day, int game, bool outcome){
    if(!outcome) game = -game;
    for(int i=0; i<n; i++) if(guesses[i][day] == game) return true;
    return false; 
}

// Performs a sequence of relatively simple checks
int main(){
    cin >> n;

    for(int i=0; i<7; i++) cin >> daysize[i];

    for(int i=0; i<n; i++){
        for(int j=0; j<7; j++) {
            cin >> guesses[i][7];
        }
    }
    
    cin >> pascal[5] >> pascal[6];
    
    // If somesone makes the same guess as Pascal, Pascal can not win
    bool fine = true;
    for(int i=0; i<n; i++) fine = fine && (guesses[i][5] != pascal[5]) || (guesses[i][6] != pascal[6]);
    terminate(fine);

/*
    // If two participants disagree on 3 days, one of them must score at least 2 points and Pascal loses
    for(int d1 = 0; d1 < 7; d1++) for(int d2 = 0; d2 < d1; d2++) for(int d3 = 0; d3 < d2; d3++){
        if(exists_guess(d1, ))

    }
*/
} 