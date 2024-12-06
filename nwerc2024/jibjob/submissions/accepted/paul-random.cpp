#include <algorithm>
#include <cmath>
#include <complex>
#include <iostream>
#include <random>
#include <vector>
using namespace std;
using i64 = long long;

const long double pi = 2*acosl(0);

// Normalizes an angle to the range [-pi,pi).
void normalize(long double &alpha) {
    while (alpha >= pi) alpha -= 2*pi;
    while (alpha < -pi) alpha += 2*pi;
}

// Computes the area of the union of some given circular disks using
// Green's theorem. A good explanation of the method can be found here:
// https://discuss.codechef.com/t/chefpc-editorial/12282
long double union_area(const vector<i64> &x, const vector<i64>& y, const vector<i64> &r) {
    int n = x.size();
    // Find which parts of the boundary of circle i are part of the boundary
    // of the overall figure using an angular sweep.
    long double res = 0;
    for (int i = 0; i < n; i++) {
        int count = 0; // Number of other circles we are currently in.
        vector<pair<long double, int>> events;
        // Loop over the other circles and for each of them find
        // the interval of angles covered by that circle.
        for (int j = 0; j < n; j++) if (j != i) {
            long double dist = hypotl(x[j]-x[i], y[j]-y[i]);

            // If dist is near-integer, round it to the closest integer.
            // This is safe, as the coordinates are small.
            if (abs(dist-round(dist)) < 1e-9) dist = round(dist);

            // If the circles are disjoint, ignore.
            if (dist >= r[i] + r[j]) continue;

            // If circle j is inside circle i, ignore.
            if (r[j] + dist <= r[i]) continue;

            // If circle i is inside circle j, increment the count.
            if (r[i] + dist <= r[j]) {
                count++;
                continue; // could also break here instead
            }

            // Note that in the comparisons above we didn't need to use
            // epsilons as equality can only happen when dist is an integer and
            // near-equality cannot happen because the coordinates are small.

            // Intersection points are at angles alpha-beta and alpha+beta.
            // Note that beta is always in [0,pi] by definition of acos. In
            // fact, as the case of touching circles was eliminated above, we
            // know that beta must be strictly inside this interval.
            long double alpha = atan2l(y[j]-y[i], x[j]-x[i]);
            long double num = dist*dist + r[i]*r[i] - r[j]*r[j];
            long double denom = 2 * dist * r[i];
            long double beta = acosl(num/denom);

            // Compute the covered interval, and add a +1 event for the start
            // of the interval and a -1 event for the end of the interval.
            long double gamma1 = alpha - beta;
            long double gamma2 = alpha + beta;
            normalize(gamma1), normalize(gamma2);
            events.emplace_back(gamma1, 1);
            events.emplace_back(gamma2, -1);

            // We start the sweep at -pi, and we need to increment the
            // count when this starting point is inside circle j.
            if (gamma1 > gamma2) count++;
        }

        // Add a "sentinel" event to cover the final stretch of the boundary
        // back to the starting point.
        events.emplace_back(pi, 0);

        // Now go over the event queue in sorted order. Whenever the count
        // drops to 0, this part of the boundary is also part of the boundary
        // of the overall shape.
        sort(begin(events), end(events));
        long double alpha = -pi;
        for (auto [beta, add]: events) {
            if (count == 0) {
                complex<long double> c(x[i], y[i]);
                complex<long double> a = polar((long double) r[i], alpha);
                complex<long double> b = polar((long double) r[i], beta);
                // Add the signed area of the circular sector and two
                // triangles, where for the latter we use complex number
                // multiplication to compute the relevant cross products.
                res += 0.5 * (r[i]*r[i]*(beta-alpha) + imag(conj(c+a)*(c+b) - conj(a)*b));
            }
            count += add;
            alpha = beta;
        }
    }
    return res;
}

int main() {
    // Read input.
    int n; cin >> n;
    vector<i64> x(n), y(n), h(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i] >> h[i];
    }

    // Compute maximum possible length for each jib.
    vector<i64> rmax(n);
    for (int i = 0; i < n; i++) {
        i64 r2max = h[i]*h[i];
        for (int j = 0; j < n; j++) {
            if (h[j] <= h[i]) continue;
            i64 dx = x[j]-x[i], dy = y[j]-y[i];
            r2max = min(r2max, dx*dx + dy*dy);
        }
        rmax[i] = sqrt(r2max);
    }

    // Compute the resulting area assuming all radii are maximized.
    auto max_area = union_area(x, y, rmax);

    mt19937 gen(987);

    // For some of the circles, randomly shrink them and check whether that
    // changes the area. If yes, revert the change. Otherwise keep it.
    vector<i64> r = rmax;
    for (int k = 0; k < 50; k++) {
        int i = uniform_int_distribution<int>(0, n-1)(gen);
        r[i] = uniform_int_distribution<int>(1, rmax[i])(gen);
        auto area = union_area(x, y, r);
        if (area < max_area - 1e-9) r[i] = rmax[i];
    }

    // Output the radii.
    for (int i = 0; i < n; i++) {
        cout << r[i] << '\n';
    }
}
