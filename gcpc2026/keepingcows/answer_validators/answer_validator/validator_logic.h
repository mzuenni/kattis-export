#include "validate.h"

using namespace std;
using namespace Verdicts;

#define sz(x) ssize(x)
using pii = pair<Integer, Integer>;
#define EMPTY  1
#define CORNER 2
#define SIDE   3
const vector<Integer> di = {-1, 1, 0, 0};
const vector<Integer> dj = {0, 0, -1, 1};

constexpr Integer MAX_SIDE_LENGTH = 100;

struct sat2 {
	int n; // + scc variablen
	vector<int> sol;
	vector<vector<int>> adj;
	int sccCounter;
	vector<int> low, idx, s; //idx enthält Index der SCC pro Knoten.

	sat2(int vars) : n(vars*2), adj(n) {}

	void addImpl(int a, int b) {
		adj[a].push_back(b);
		adj[1^b].push_back(1^a);
	}
	void addEquiv(int a, int b) {addImpl(a, b); addImpl(b, a);}
	void addOr(int a, int b) {addImpl(1^a, b);}
	void addXor(int a, int b) {addOr(a, b); addOr(1^a, 1^b);}
	void addTrue(int a) {addImpl(1^a, a);}
	void addFalse(int a) {addTrue(1^a);}
	void addAnd(int a, int b) {addTrue(a); addTrue(b);}
	void addNand(int a, int b) {addOr(1^a, 1^b);}

	bool solve() {
		scc();
		sol.assign(n, -1);
		for (int i = 0; i < n; i += 2) {
			if (idx[i] == idx[i + 1]) return false;
			sol[i] = idx[i] < idx[i + 1];
			sol[i + 1] = !sol[i];
		}
		return true;
	}

	void visit(int v) {
		int old = low[v] = sz(s);
		s.push_back(v);

		for (auto u : adj[v]) {
			if (low[u] < 0) visit(u);
			if (idx[u] < 0) low[v] = min(low[v], low[u]);
		}

		if (old == low[v]) {
			for (int i = old; i < sz(s); i++) idx[s[i]] = sccCounter;
			sccCounter++;
			s.resize(old);
	}}

	void scc() {
		low.assign(sz(adj), -1);
		idx.assign(sz(adj), -1);

		sccCounter = 0;
		for (int i = 0; i < sz(adj); i++) {
			if (low[i] < 0) visit(i);
	}}
};

void performValidation(Integer targetArea, InputStream& in, OutputStream& juryOut, const Verdict verdict){
	// parse grid
	Integer h = in.integer(1, MAX_SIDE_LENGTH + 1);
	in.space();
	Integer w = in.integer(1, MAX_SIDE_LENGTH + 1);
	in.newline();
	vector<string> rawGrid;
	for(Integer i = 0; i < h; i++){
		rawGrid.push_back(in.string(ValidateBase::caseSensitive.regex("[#O.]+"), w, w+1));
		in.newline();
	}
	in.eof();
	vector<vector<Integer>> grid(h, vector<Integer>(w, -1));
	for(Integer i = 0; i < h; i++){
		for(Integer j = 0; j < w; j++){
			if(rawGrid[i][j] == '.')      grid[i][j] = EMPTY;
			else if(rawGrid[i][j] == '#') grid[i][j] = SIDE;
			else                          grid[i][j] = CORNER;
		}
	}
	// check for valid component
	auto isInsideGrid = [&](Integer i, Integer j){
		return 0 <= i && i < h && 0 <= j && j < w;
	};
	bool hasValidComponent = false;
	vector<vector<bool>> vis(h, vector<bool>(w));
	for(Integer si = 0; si < h; si++){
		for(Integer sj = 0; sj < w; sj++){
			if(vis[si][sj]) continue;
			if(grid[si][sj] != EMPTY) continue;
			int area = 0;
			bool canGoOutside = false;
			vector<pii> stck;
			stck.emplace_back(si, sj);
			vis[si][sj] = true;
			while(!stck.empty()){
				area++;
				auto [i, j] = stck.back();
				stck.pop_back();
				for(Integer d = 0; d < 4; d++){
					Integer i2 = i + di[d];
					Integer j2 = j + dj[d];
					if(!isInsideGrid(i2, j2)){
						canGoOutside = true;
					}
					else if(grid[i2][j2] == EMPTY && !vis[i2][j2]){
						vis[i2][j2] = true;
						stck.emplace_back(i2, j2);
					}
				}
			}
			if(!canGoOutside && area == targetArea) hasValidComponent = true;
		}
	}
	if(!hasValidComponent){
		juryOut << "No component of area " << targetArea << verdict;
	}
	// check whether grid really consists of L-fences
	// step 1: check number of corners * 2 == number of sides
	Integer cntCorner = 0;
	Integer cntSide = 0;
	vector<vector<Integer>> cornerId(h, vector<Integer>(w, -1));
	for(Integer i = 0; i < h; i++){
		for(Integer j = 0; j < w; j++){
			if(grid[i][j] == CORNER){
				cornerId[i][j] = cntCorner;
				cntCorner++;
			}
			if(grid[i][j] == SIDE) cntSide++;
		}
	}
	if(2*cntCorner != cntSide){
		juryOut << "Number of corners: " << cntCorner << ", number of sides: " << cntSide << ", this is impossible" << verdict; 
	}
	// step 2: 2-SAT (for every O the decision in each dimension is independent)
	// variables:
	//   (corner, dir) -> dir + 2*corner
	//   "Is the corner matched in positive direction along dir-axis?"
	//   dir=0 -> i, dir=1 -> j
	//   e.g. if corner c at (i,j) has variable (c,1)=false, then it's matched with (i,j-1)
	// this gives us the following meaning of literals corresponding to corner c at (i,j):
	//   4c+0: matched with (i+1,j  )
	//   4c+1: matched with (i-1,j  )
	//   4c+2: matched with (i  ,j+1)
	//   4c+3: matched with (i  ,j-1)
	sat2 sat(2*cntCorner);
	for(Integer i = -1; i <= h; i++){
		for(Integer j = -1; j <= w; j++){
			vector<Integer> adjacentLiterals;
			for(Integer d = 0; d < 4; d++){
				Integer i2 = i + di[d];
				Integer j2 = j + dj[d];
				if(isInsideGrid(i2, j2) && cornerId[i2][j2] != -1){
					adjacentLiterals.push_back(cornerId[i2][j2]*4 + d);
				}
			}
			if(isInsideGrid(i, j) && grid[i][j] == SIDE){
				for(Integer p = 0; p < sz(adjacentLiterals); p++){
					for(Integer q = 0; q < p; q++){
						sat.addNand(adjacentLiterals[p], adjacentLiterals[q]);
					}
				}
			}
			else{
				for(Integer lit : adjacentLiterals){
					sat.addFalse(lit);
				}
			}
		}
	}
	if(!sat.solve()){
		juryOut << "2SAT solver didn't find way to assign L-fences" << verdict;
	}
}
