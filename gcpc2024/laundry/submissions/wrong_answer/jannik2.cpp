#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

using i64 = int64_t;
using u8 = uint8_t;

constexpr i64 oo = 0x3f3f3f3f3f3f3f3fLL;

int main()
{
	i64 t; 
	cin >> t; 
	while(t--) {
		i64 k;
		cin >> k;
		i64 a, b, c, ab, bc, ac, abc;
		cin >> a >> b >> c >> ab >> bc >> ac >> abc;

		vector<pair<u8, i64>> todo = { { 0b011, ab }, { 0b110, bc }, { 0b101, ac }, { 0b111, abc } };
		i64 res = oo;
		do {
			for (i64 abc_i = 0; abc_i < 3; abc_i++) {
				vector<i64> cur = { a, b, c };
				for (auto [t, n] : todo) {
					if (t == 0b111) {
						for (i64 i = 0; i < 3; i++) {
							i64 cap = ((cur[i] + k - 1) / k) * k - cur[i];
							cap = min(cap, n);
							cur[i] += cap;
							n -= cap;
						}
						cur[abc_i] += n;
						continue;
					}
					i64 ans = oo, ans_i = -1;
					for (i64 i = 0; i < 3; i++)
						if (t & (1u << i)) {
							i64 x = (cur[i] + n + k - 1) / k - (cur[i] + k - 1) / k;
							if (x < ans)
								ans = x, ans_i = i;
						}
					cur[ans_i] += n;
				}

				i64 ans = 0;
				for (i64 x : cur)
					ans += (x + k - 1) / k;
				res = min(res, ans);
			}
		} while (next_permutation(todo.begin(), todo.end()));
		cout << res << endl;
	}
	return 0;
}
