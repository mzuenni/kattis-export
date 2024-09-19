#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;
using pt = pair<ll, ll>;

void fastscan(ll& number) {
	bool negative = false;
	int c;
	number = 0;
	c = getchar();
	while(c != '-' && (c < '0' || c > '9')) c = getchar();
	if (c == '-') negative = true, c = getchar();
	for (; c >= '0' && c <= '9'; c = getchar()) number = number * 10 + c - '0';
	if (negative) number *= -1;
}

void printPositive(ll n) {
	if (n == 0) return;
	printPositive(n / 10);
	putchar(n % 10 + '0');
}

void fastprint(ll n) {
	if(n == 0) {putchar('0'); return;}
	if (n < 0) {
		putchar('-');
		printPositive(-n);
	} else printPositive(n);
}


pt readPT() {
	ll x, y;
	fastscan(x);
	fastscan(y);
	return pt(x, y);
}

pt sub(pt a, pt b) {
	return {a.first - b.first, a.second - b.second};
}

// Kreuzprodukt, 0, falls kollinear.
ll cross(pt a, pt b) {return a.first * b.second - a.second * b.first;}
ll cross(pt p, pt a, pt b) {return cross(sub(a, p), sub(b, p));}

// -1 => gegen den Uhrzeigersinn
//  0 => kolliniear
//  1 => im Uhrzeigersinn.
ll orientation(pt a, pt b, pt c) {
	ll orien = cross(a, b, c);
	return (orien > 0) - (orien < 0);
}

constexpr ll inf = 0x3FFFFFFF;

ll len(pt a) {
	return abs(a.first) + abs(a.second);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	ll n, m; // number of corners of the polygon and number of points to print
	fastscan(n);
	fastscan(m);

	vector<pt> in(n);
	for (ll i = 0; i < n; i++) in[i] = readPT();
	in.push_back(in[0]);

	pt s = readPT(); // start point must be on polygon and not a corner | could always be (0,0)
	pt d(1,1);

	for (ll i = 0; i < m; i++) {
		ll steps = inf;
		pt nextDir = d;
		for (ll j = 0; j < n; j++) {
			pt t(s.first + d.first, s.second + d.second);
			if (orientation(s, t, in[j]) * orientation(s, t, in[j+1]) <= 0) {
				ll curSteps;
				pt curDir;
				if (in[j].first == in[j+1].first) {
					curSteps = (in[j].first - s.first) * d.first;
					curDir = {-d.first, d.second};
				} else {
					curSteps = (in[j].second - s.second) * d.second;
					curDir = {d.first, -d.second};
				}
				if (curSteps > 0 && curSteps < steps) {
					steps = curSteps;
					nextDir = curDir;
				}
			}
		}
		s.first += d.first*steps;
		s.second += d.second*steps;
		d = nextDir;
		fastprint(s.first);
		putchar(' ');
		fastprint(s.second);
		putchar('\n');
	}
}
