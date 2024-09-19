#include <iostream>
#include <algorithm>
#include <array>
#include <iomanip>
#include <vector>

using namespace std;

using ll = long long;

#define sz(a) ll((a).size())

template<size_t N, size_t M>
struct Mat {
	array<array<double, M>, N> a;
	Mat(double x = 0) {
		for (size_t i = 0; i < N; i++)
			for (size_t j = 0; j < M; j++)
				a[i][j] = (i == j ? x : 0.);
	}
};

template<size_t N, size_t M, size_t K>
Mat<N,K> operator*(const Mat<N,M>& a, const Mat<M,K>& b) {
	Mat<N,K> res(0);
	for (size_t i = 0; i < N; i++)
		for (size_t j = 0; j < K; j++)
			for (size_t k = 0; k < M; k++)
				res.a[i][j] += a.a[i][k] * b.a[k][j];
	return res;
}

template<typename T>
T pow(const T& a, ll n) {
	if (n == 0) return T{1};
	T b = pow(a, n/2);
	b = b * b;
	if (n % 2 == 1) b = b * a;
	return b;
}

int main() {
	ll n;
	cin >> n;
	n--;

	Mat<2,2> op(0);
	op.a[0][1] = 1;
	op.a[1][0] = op.a[1][1] = 0.5;

	op = pow(op, n);

	Mat<2,1> res;
	res.a[0][0] = 100;
	res.a[1][0] = 0;

	res = op * res;

	cout << fixed << setprecision(10) << res.a[0][0] << ' ' << (100 - res.a[0][0]) << endl;

	return 0;
}
