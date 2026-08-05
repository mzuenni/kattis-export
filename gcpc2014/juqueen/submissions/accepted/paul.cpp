#include <bits/stdc++.h>
using namespace std;

template<typename T, typename U>
struct segtree {
	int n, H;
	
	vector<T> value;
	vector<U> prop;
	vector<bool> dirty;

	segtree(vector<T> leaves): n(leaves.size()), value(2*n), prop(n), dirty(n) {
		H = 32 - __builtin_clz(2*n-1);
		copy(begin(leaves), end(leaves), begin(value)+n);
		for (int i = n-1; i >= 1; i--) {
			value[i] = value[2*i] + value[2*i+1];
		}
	}

	void apply(int i, U &upd) {
		value[i] = upd(value[i]);
		if (i < n) prop[i] = prop[i] + upd, dirty[i] = true;
	}

	void rebuild(int i) {
		for (i /= 2; i; i /= 2) value[i] = prop[i](value[2*i] + value[2*i+1]);
	}

	void propagate(int i) {
		for (int h = H; h >= 1; h--) if (dirty[i >> h]) {
			int j = i >> h;
			apply(2*j,prop[j]), apply(2*j+1,prop[j]);
			prop[j] = U(), dirty[j] = false;
		}
	}

	void update(int i, int j, U upd) {
		if (i == j) return;
		i += n, j += n;
		propagate(i), propagate(j-1);
		for (int l = i, r = j; l < r; l /= 2, r /= 2) {
			if (l & 1) apply(l++,upd);
			if (r & 1) apply(--r,upd);
		}
		rebuild(i), rebuild(j-1);
	}
	
	T query(int i, int j) {
		i += n, j += n;
		propagate(i), propagate(j-1);
		T resl, resr;
		for (; i < j; i /= 2, j /= 2) {
			if (i & 1) resl = resl + value[i++];
			if (j & 1) resr = value[--j] + resr;
		}
		return resl + resr;
	}
};

struct node {
    int lo = INT_MAX, hi = INT_MIN;
	node operator+(const node &n) const {
        return node{min(lo, n.lo), max(hi, n.hi)};
    }
};

struct update {
    int add = 0;
	node operator()(const node &n) const {
        return node{n.lo+add, n.hi+add};
    }
	update operator+(const update &u) const {
        return update{add+u.add};
    }
};


int main() {
    int n, m, q;
    cin >> n >> m >> q;

    vector<node> leaves(n, node{0, 0});
    segtree<node,update> S(leaves);
    while (q--) {
        string t; cin >> t;
        if (t == "state") {
            int x; cin >> x;
            cout << S.query(x, x+1).lo << '\n';
        } else {
            int a, b, s;
            cin >> a;
            if (t == "change") b = a; else cin >> b;
            cin >> s;
            b++;
            auto [lo, hi] = S.query(a, b);
            s = max(s, -lo);
            s = min(s, m-hi);
            S.update(a, b, update{s});
            cout << s << '\n';
        }
    }
}
