// @EXPECTED_RESULTS@: TIMELIMIT
// naive integration with adaptive precision.
// kristof, please make up your mind whether this should pass, 
// and whether we need testcases against this case.
// -> Shouldn't pass in my opinion, since the testcase for
// maximum precision didn't exploit the maximum size of the
// input. Since it does, this solution doesn't pass anymore.


#include <iostream>
#include <limits>
#include <cmath>
#include <iomanip>

using namespace std;

const double PI = 3.141592653589793238463;

struct FlowerPot {
  double a;
  double b;
  double h;
};

double integrate(const FlowerPot& pot, double precisionHint) {
	double divisor;
	if(precisionHint < 0.0001)
		divisor = 1e-6;
	else
		divisor = 1e-5;
	int numberOfSteps = ceil(pot.h / divisor);
	double dx = pot.h/(double)numberOfSteps;
	double volume = 0.0;
	
	double x = 0;
	double a = pot.a;
	double b = pot.b;
	for(int step = 0; step < numberOfSteps; step++) {
		x += dx;
		double value = a * exp(-x*x) + b * sqrt(x);
		volume += value * value;
	}
	
	return volume * dx * PI;
}

FlowerPot p[1000];

int main() {

  int testcases;
  
  //cin >> testcases;
  testcases = 1;
  
  for(int testcase = 0; testcase < testcases; testcase++) {
    double v;
    cin >> v;
    int n;
    cin >> n;

    double bestVolume = -numeric_limits<double>::max();
    int bestIndex = -1;

    for (int i = 0; i < n; i++) {
      cin >> p[i].a;
      cin >> p[i].b;
      cin >> p[i].h;
      
    }
    
    double mindiff =  numeric_limits<double>::max();
    for(int i = 0; i < n; i++) {
	    for(int j = 0; j < n; j++) {
		    if(i == j) continue;
		    double d1 = abs(p[i].a - p[j].a);
		    double d2 = abs(p[i].b - p[j].b);
		    double d3 = abs(p[i].h - p[j].h);
		    double dm;
		    if(d1 >= d2 && d1 >= d3) {
			    dm = d1;
		    } else if(d2 >= d1 && d2 >= d3){
			    dm = d2;
		    } else {
			    dm = d3;
		    }
		    if(mindiff > dm) mindiff = dm;
	    }
    }
    cerr << mindiff << endl;
    for (int i = 0; i < n; i++) {
	    double volume = integrate(p[i], mindiff);
      
      if(abs(volume - v) < abs(bestVolume -v)) {
        bestVolume = volume;
        bestIndex = i;
      }
    }
    
    cout << bestIndex << endl;
  }

  return 0;
}

