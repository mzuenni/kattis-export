// @EXPECTED_RESULTS@: WRONG-ANSWER

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

double function(const FlowerPot& pot, double x) {
  double value = pot.a * exp(-x*x) + pot.b * sqrt(x);
  return value * value * PI;
}

double integrate(const FlowerPot& pot) {
  int numberOfSteps = ceil(pot.h / 1e-5);
  double dx = pot.h/(double)numberOfSteps;
  double volume = 0.0;
  
  for(int step = 0; step < numberOfSteps; step++) {
    double x = step * dx;
    double value = function(pot, x);
    volume += value * dx;
  }
  
  return volume;
}

int main() {

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
    
    if(abs(volume - v) < abs(bestVolume -v)) {
      bestVolume = volume;
      bestIndex = i;
    }
  }
  
  cout << bestIndex << endl;

  return 0;
}

