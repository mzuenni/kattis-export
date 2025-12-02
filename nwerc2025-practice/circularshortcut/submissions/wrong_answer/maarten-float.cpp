#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

int main() {
    float d;
    cin >> d;
    cout << setprecision(42) << d * M_PIl / 2 - d << endl;
}