#include <bits/stdc++.h>
using namespace std;

/* Finds the minimal number of moves by backwards
 * breadth-first-search starting from the final
 * states (those where the squirrel is captured).
 *
 * Time complexity: O(n^4)
 */

#define FOR(i,a,b) for (int i = (a); i < (b); i++)

/* p = 0: ravens to move, p = 1: squirrel to move
 * r1, r2: ravens' positions, s: squirrel's position
 * for p = 1: the raven at r1 is the one sitting in the tree
 *            and r2 is the position the other raven will land on
 */

struct state {
	int p, r1, r2, s;

	int outdegree = 0;
	vector<state*> reverse_moves;
	
	int game_duration = 0;
	bool visited = false;

	void add_edge(state *nxt) {
		nxt->reverse_moves.push_back(this);
		outdegree++;
	}

	state(int p, int r1, int r2, int s): p(p), r1(r1), r2(r2), s(s) { }
};

const int N = 100;
state *st[2][N][N][N];

int main() {
	int n, S, R1, R2; // number of nodes, squirrel, raven 1, raven 2
	cin >> n >> S >> R1 >> R2;
	S--, R1--, R2--;

	vector<vector<int>> adj(n);
	for (int i = 1; i < n; i++) {
		int a, b; cin >> a >> b;
		a--, b--;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	
	FOR(p,0,2) FOR(r1,0,n) FOR(r2,0,n) FOR(s,0,n) st[p][r1][r2][s] = new state(p,r1,r2,s);
	
	FOR(r1,0,n) FOR(r2,0,n) if (r1 != r2) FOR(s,0,n) {
		// ravens' moves:
		FOR(r3,0,n) if (r3 != r1 && r3 != r2)
			st[0][r1][r2][s]->add_edge(st[1][r2][r3][s]);
		FOR(r3,0,n) if (r3 != r1 && r3 != r2)
			st[0][r1][r2][s]->add_edge(st[1][r1][r3][s]);
		
		// squirrel's moves:
		vector<bool> reach(n);
		queue<int> q;
		reach[s] = true;
		q.push(s);
		while (q.size()) {
			int s1 = q.front(); q.pop();
			if (s1 == r1) continue; // moving past r2 or stopping there is fine
			                        // (the latter results in capture)
			for (int s2: adj[s1]) if (!reach[s2])
				reach[s2] = true, q.push(s2);
			st[1][r1][r2][s]->add_edge(st[0][r1][r2][s1]);
		}
	}

	queue<state*> q;
	FOR(s,0,n) FOR(r1,0,n) if (s != r1) {
		// final states: squirrel is at same position as the raven
		//               that moved last, with the ravens to move next
		state *cur = st[0][r1][s][s];
		cur->game_duration = 0;
		cur->visited = true;
		q.push(cur);
	}
	
	while (q.size()) {
		state *cur = q.front(); q.pop();
		
		for (state *nxt: cur->reverse_moves) {
			if (nxt->visited) continue;
			nxt->outdegree--;
			if (nxt->p == 0) {
				nxt->game_duration = 1 + cur->game_duration;
			} else {
				nxt->game_duration = max(nxt->game_duration, cur->game_duration);
				if (nxt->outdegree > 0) continue;
			}
			nxt->visited = true;
			q.push(nxt);
		}
	}
	
	assert(st[0][R1][R2][S]->visited);
	cout << st[0][R1][R2][S]->game_duration << endl;
}
