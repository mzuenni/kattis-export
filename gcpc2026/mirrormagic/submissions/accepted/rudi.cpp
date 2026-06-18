#include<bits/stdc++.h>
using namespace std;

const int MAXN = 200000;
typedef long double coord;

// mostly copy-and-paste from my TL submission, but with the actual solution method

struct point{
    coord x, y;
    point operator+(point p) const { return point{x + p.x, y + p.y};}
    point operator*(coord f) const { return point{x * f, y * f};}
    point operator-(point p) const { return point{x - p.x, y - p.y};}
};
bool operator<( const point &a,const point &b)
{
    return a.x < b.x ||( a.x == b.x && a.y < b.y);
}   

coord sqd(point a, point b){
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

int n;

vector<point> a;
vector<point> b;

set<point> sb;

void accept(){
    cout << "possible" << endl;
    exit(0);
}

void reject(){
    cout << "impossible" << endl;
    exit(0);
}

point mid_point(point a, point b){
    return point{a.x + b.x, a.y + b.y} * 0.5;
}

void read(vector<point> & input){

    for(int i=0; i<n; i++){
        point p;
        cin >> p.x >> p.y;
        input.push_back(p);
    }
}

point round_point(point p){
    return{round(p.x), round(p.y)};
}

bool is_integer(point p){
    return sqd(p, round_point(p)) < 0.0001;
}


// Geometrie-Unsinn
point project(point a, point b, point c){
    point ab = b - a;
    point ac = c - a;

    // dot product to get the distance on the line??
    coord lambda = (ab.x * ac.x + ab.y * ac.y) / sqd(ab, {0, 0}); 
    return a + ab * lambda;
}
point mirror(point a, point b, point c){
    point projection = project(a, b, c);
    return projection + (projection - c);
}
coord side_value(point a, point b, point c){
    return (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);
}

// Checks wheter all points of points lie to the same side of ab as the reference point
void side_check(point a, point b, vector<point> & points, point reference){
    coord ref_val = side_value(a, b, reference);
    for(point p: points){
        coord val = side_value(a, b, p);
        if(abs(val) < 0.0001) reject(); // point lies on the mirror line
        if(val * ref_val < 0) reject(); // point lies on the opposite side of the mirror line
    }
}


int main(){
    cin >> n;

    read(a);
    read(b);

    if(n == 1) accept();

    point center_a = {x: 0, y: 0};
    for(auto p: a) center_a = center_a + p * (1.0 / n);

    point center_b = {x: 0, y: 0};
    for(auto p: b) center_b = center_b + p * (1.0 / n);

    if(sqd(center_a, center_b) < 0.01) reject();

    
    point first = mid_point(center_a, center_b); // first point on the mirrow line
    point vec = {center_b.y - center_a.y, center_a.x - center_b.x};
    point second = first + (vec * 100); // second point on the mirror line


    // The mirror must separate a from b. Do some geometry stuff to check this
    side_check(first, second, a, center_a);
    side_check(first, second, b, center_b);


    // Now check if each point in a has a partner in b
    for(auto b : b) sb.insert(b);
    
    for(auto p : a){
        point proj = mirror(first, second, p);
        if(!is_integer(proj)) reject();
        point rounded = round_point(proj);
        if(sb.count(rounded) == 0) reject();
    }

    accept();
}