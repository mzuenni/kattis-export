// @EXPECTED_RESULTS@: TIMELIMIT
// naive integration, somewhat optimized.
// this should not pass, but it almost does.


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

double integrate(const FlowerPot& pot) {
  int numberOfSteps = ceil(pot.h / 1e-6);
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
      FlowerPot pot;
      cin >> pot.a;
      cin >> pot.b;
      cin >> pot.h;
      
      double volume = integrate(pot);
      
      //std::cout << "volume= " << setprecision(12) << volume << std::endl;
      
      if(abs(volume - v) < abs(bestVolume -v)) {
        bestVolume = volume;
        bestIndex = i;
      }
    }
    
    cout << bestIndex << endl;
  }

  return 0;
}

