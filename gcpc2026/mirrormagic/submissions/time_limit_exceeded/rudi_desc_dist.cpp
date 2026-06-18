#include<bits/stdc++.h>
using namespace std;

/**
 * Greedily search for two points pa, pb
 * s.t. pa has minimum distance to pb among all point in A and vice versa
 * Then pa and pb have to be mirrored (probably?)
 * The Greedy process is guaranteed to terminate in O(n) steps, but each step takes O(n) time...s 
 */

const int MAXN = 200000;
typedef long double coord;

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

point mid_point(point a, point b){
    return point{a.x + b.x, a.y + b.y} * 0.5;
}

coord sqd(point a, point b){
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

int n;

vector<point> a;
vector<point> b;

set<point> sb;

pair<point, coord> find_closest_point(point p, vector<point> & points){
    coord minim = sqd(p, points[0]);
    point argmin = points[0];
    for(point x: points){
        coord d = sqd(p, x);
        if(d < minim){
            minim = d;
            argmin = x;
        }
    }
    return {argmin, minim};
}

void accept(){
    cout << "possible" << endl;
    exit(0);
}

void reject(){
    cout << "impossible" << endl;
    exit(0);
}

point random_point(vector<point> & points){
    return points[rand() % points.size()];
}

pair<point, point> find_mirror_pair(){
    point cur_a = random_point(a);
    point cur_b = random_point(b);
    coord cur_d = sqd(cur_a, cur_b);

    while(true){
        auto [new_b, d] = find_closest_point(cur_a, b);
        if(d < cur_d){
            cur_d = d;
            cur_b = new_b;
            continue;
        }

        auto [new_a, dd] = find_closest_point(cur_b, a);
        if(dd < cur_d){
            cur_d = dd;
            cur_a = new_a;
            continue;
        }
        break;
    }
    return {cur_a, cur_b};
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

    auto [pa, pb] = find_mirror_pair();


    point mid = mid_point(pa, pb);
    point vec = {pb.y - pa.y, pa.x - pb.x};
    point second = mid + (vec * 100); // second point on the mirror line

    // The mirror must separate a from b. Do some geometry stuff to check this
    side_check(mid, second, a, pa);
    side_check(mid, second, b, pb);

    // Now check if each point in a has a partner in b
    for(auto b : b) sb.insert(b);
    
    for(auto p : a){
        point proj = mirror(mid, second, p);
        //printf("Projecting (%Lf, %Lf) onto (%Lf, %Lf)\n", p.x, p.y, proj.x, proj.y);
        if(!is_integer(proj)) reject();
        point rounded = round_point(proj);
        if(sb.count(rounded) == 0) reject();
    }

    accept();
}