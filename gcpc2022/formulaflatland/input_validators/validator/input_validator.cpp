#include "validate.h"
using namespace std;

using namespace ctd;

#define all(x) begin(x), end(x)
#define sz(x) (Integer)(x).size()

struct coord_t {
  Integer x, y;
};

int main(int argc, char **argv) {
	using namespace InputValidator;
	InputValidator::init(argc, argv);

	Integer n, m;
	testIn >> INT(4, 100001, n) >> SPACE >> INT(6, 300001, m) >> NEWLINE;
	vector<coord_t> pos;
	set<pair<Integer, Integer>> seenPos;
	for (Integer i = 0; i < n; i++) {
		Integer x, y;
		testIn >> INT(0, 1000000001, x) >> SPACE >> INT(0, 1000000001, y) >> NEWLINE;
		if (x == y) 
		if (seenPos.find({x, y}) != seenPos.end()) juryOut << "Duplicate position: (" << x << "," << y << ")" << WA;
		pos.push_back({x, y});
		seenPos.insert({x, y});
	}

	vector<Integer> deg(n);
	vector<pair<Integer, Integer>> edgeList;
	for (Integer i = 0; i < m; i++) {
		Integer a, b;
		testIn >> INT(1, n+1, a) >> SPACE >> INT(1, n+1, b) >> NEWLINE;
		if (a == b) juryOut << "Selfloop: " << a << "<->" << a << WA;
		a--;
		b--;
		deg[a]++;
		deg[b]++;
		if (a < b) swap(a, b);
		edgeList.push_back({a, b});
	}
	testIn >> ENDFILE;
	sort(all(edgeList));
	for (Integer i = 0; i + 1 < m; i++) {
		if (edgeList[i] == edgeList[i + 1]) juryOut << "Multi-edge: " << edgeList[i].first << "<->" << edgeList[i].second << WA;
	}
	for (Integer i = 0; i < n; i++) {
		if (deg[i] <= 2) juryOut << "Min-degree too small: " << i+1 << WA;
	}

	// check graph planar
	// check graph straight line
	// this was done offline with boost

	return AC;

}
