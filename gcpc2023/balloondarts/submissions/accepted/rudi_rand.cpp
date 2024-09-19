#include<bits/stdc++.h>
using namespace std;

vector<pair<int, int>> points;
vector<int> indexv[5];
vector<int> tmp;

int gcd(int a, int b) {
    if (a == 0) return b;
    return gcd(b % a, a);
}

mt19937 rng(123456789);
int randomElement(vector<int> v) {
	return v[uniform_int_distribution<int>(0, v.size())(rng)];
}

// assumes i1 != i2
bool iscolinear(int i1, int i2, int i3){
    if(i3 == i1 || i3 == i2) return true;
    int dx = points[i2].first - points[i1].first;
    int dy = points[i2].second - points[i1].second;

    if(dx == 0) return points[i1].first == points[i3].first;
    if(dy == 0) return points[i1].second == points[i3].second;

    int ggt = gcd(abs(dx), abs(dy));
    dx /= ggt;
    dy /= ggt;

    int difx = points[i3].first - points[i1].first;
    int dify = points[i3].second - points[i1].second;

    if(abs(difx) % abs(dx)) return false;
    if(abs(dify) % abs(dy)) return false;

    return difx / dx * dy == dify;
}

void removePointsOnLine(int i1, int i2, vector<int> & indices){
    tmp.clear();
    for(int i : indices) tmp.push_back(i);
    indices.clear();
    for(int i3 : tmp) if(!iscolinear(i1, i2, i3)) indices.push_back(i3);
}

int countPointsOnLine(int i1, int i2, vector<int> & indices){
    int cnt = 0;
    for(int i3 : indices) if(iscolinear(i1, i2, i3)) cnt++;
    return cnt;
}

void testcolin(){
    int a, b;
    for(int i=0; i<3; i++){
        cin >> a >> b;
        points.push_back({a, b});
    }
    cout << iscolinear(0, 1, 2);   
}

void copy(vector<int> & v1, vector<int> & v2){
    v2.clear();
    for(int i : v1) v2.push_back(i);
}

void outputLine(int i1, int i2){
    cout << "(" << points[i1].first  << ", " << points[i1].second << ") - (" << points[i2].first  << ", " << points[i2].second << ")" << endl;
}

bool solveRest(int lines, vector<int> & indices){
    if(lines == 0) return indices.empty();
    //cout << lines << " " << indices.size() << endl;
    if(indices.size() <= 2) return true;

    if(lines == 1){
        int i1 = indices[0];
        int i2 = indices[1];

        for(int i3 : indices) if(!iscolinear(i1, i2, i3)) return false;
        //outputLine(i1, i2);
        return true;
    }

    for(int i1 : indices){
        for(int i2: indices){
            if(i2 == i1) continue;
            copy(indices, indexv[lines - 1]);
            //cout << "a: " << indexv[lines-1].size() << endl;
            removePointsOnLine(i1, i2, indexv[lines - 1]);
            //cout << "b: " << indexv[lines-1].size() << endl;

            if(solveRest(lines - 1, indexv[lines - 1])) return true;
        }
    }
    return false;
}

bool solve(vector<int> & indices){
    int n;
    cin >> n;

    for(int i=0; i<n; i++){
        int x, y;
        cin >> x >> y;
        points.push_back({x, y});
        indices.push_back(i);
    }

    int tries = 0;
    int lines = 3;
    while(indices.size() >= 10 && lines >= 0){
        if(tries > 100) return false;
        // find line that crosses at least 4 points
        int i1 = randomElement(indices);
        int i2 = randomElement(indices);
        if(i1 == i2) continue;
        tries++;
        
        if(countPointsOnLine(i1, i2, indices) >= 4){
            lines--;
            
            //outputLine(i1, i2);
            removePointsOnLine(i1, i2, indices);
        }
    }
    if(lines < 0) return false;

    //cout << indices.size() << endl;
    copy(indices, indexv[lines]);
    return solveRest(lines, indexv[lines]);
}

int main(){
    if(solve(indexv[4])) cout << "possible" << endl;
    else cout << "impossible" << endl;

}