// @EXPECTED_RESULTS@: WRONG_ANSWER, RUN_TIME_ERROR
#include <bits/stdc++.h>
using namespace std;

int n, k;
string s, t;
queue<pair<int, int> > ans;

std::mt19937_64 rng;
struct Node {
	int val;
	int weight, size;
	Node *left, *right, *parent;
	Node(int c) : val(c), weight(rng()), size(1), left(NULL), right(NULL), parent(NULL) {}
} *root;

int size(Node *treap) { return treap ? treap->size : 0; }

void split(Node *treap, Node *&left, Node *&right, int val) {
	if (!treap) {
		left = right = NULL;
		return;
	}

	if (size(treap->left) < val) {
		split(treap->right, treap->right, right, val - size(treap->left) - 1);
		left = treap;
	} else {
		split(treap->left, left, treap->left, val);
		right = treap;
	}
	treap->size = 1 + size(treap->left) + size(treap->right);
	if (treap->left) treap->left->parent = treap;
	if (treap->right) treap->right->parent = treap;
}

void merge(Node *&treap, Node *left, Node *right) {
	if (left == NULL) {
		treap = right;
		return;
	}
	if (right == NULL) {
		treap = left;
		return;
	}

	if (left->weight < right->weight) {
		merge(left->right, left->right, right);
		treap = left;
	} else {
		merge(right->left, left, right->left);
		treap = right;
	}
	treap->size = 1 + size(treap->left) + size(treap->right);
	if (treap->left) treap->left->parent = treap;
	if (treap->right) treap->right->parent = treap;
}

int find_index(Node *treap)
{
	if (!treap) return 0;
	if (!treap->parent) return 0;
	if (treap->parent->right == treap) return 1 + size(treap->parent->left) + find_index(treap->parent);
	else return find_index(treap->parent);
}

void debug_print(Node *treap = root)
{
	if (!treap) return;
	debug_print(treap->left);
	cout << treap->val << ' ';
	debug_print(treap->right);
}

void operation(int i, int j)
{
	ans.push({i+1, j+1});
	Node *a, *b, *c, *d, *e, *f;
	if (j >= i+k)
	{
		split(root, a, b, j+1);
		split(a, c, d, i+k);
		split(c, e, f, i);
		// e-f-d-b
		merge(c, e, d);
		merge(a, c, f);
		merge(root, a, b);
	}
	else
	{
		split(root, a, b, i+k);
		split(a, c, d, i);
		split(c, e, f, j);
		merge(c, e, d);
		merge(a, c, f);
		merge(root, a, b);
	}
}

int main()
{
	rng.seed(3141592653);
	cin >> n >> k;
	std::vector<int> s(n), t(n);
	for (int i = 0; i < n; i++) cin >> s[i];
	for (int i = 0; i < n; i++) t[i] = i+1;

	if (n <= k)
	{
		for (int i = 0; i < n; i++)
		{
			if (s[i] != t[i]) return !printf("impossible\n");
		}
		return !printf("0\n");
	}
	if (n == k+1)
	{
		// Preparation for Z-algorithm
		std::vector<int> u(2*n+1), v(2*n+1);
		for (int i = 0; i < n; i++) u[i] = s[i];
		u[n] = -1; // Separator
		for (int i = 0; i < n; i++) u[n+1+i] = t[i];
		for (int i = 0; i < n; i++) v[i] = t[i];
		v[n] = -1; // Separator
		for (int i = 0; i < n; i++) v[n+1+i] = s[i];

		// Z-algorithm, implementation from Codeforces
		int m = 2*n+1, z1[m], z2[m], L = 0, R = 0;
		for (int i = 1; i < m; i++)
		{
			if (i > R)
			{
				L = R = i;
				while (R < m && u[R-L] == u[R]) R++;
				z1[i] = R-L; R--;
			}
			else
			{
				int k = i-L;
				if (z1[k] < R-i+1) z1[i] = z1[k];
				else
				{
					L = i;
					while (R < m && u[R-L] == u[R]) R++;
					z1[i] = R-L; R--;
				}
			}
		}
		L = R = 0;
		for (int i = 1; i < m; i++)
		{
			if (i > R)
			{
				L = R = i;
				while (R < m && v[R-L] == v[R]) R++;
				z2[i] = R-L; R--;
			}
			else
			{
				int k = i-L;
				if (z2[k] < R-i+1) z2[i] = z2[k];
				else
				{
					L = i;
					while (R < m && v[R-L] == v[R]) R++;
					z2[i] = R-L; R--;
				}
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (z1[n+1+i] + z2[n+1+n-i] >= n-1)
			{
				printf("%d\n", i);
				for (int x = 0; x < i; x++)
				{
					printf("%d %d\n", 1, 1 + k);
				}
				return 0;
			}
		}
		return !printf("impossible\n");
	}

	// Now we know n >= k+2.
	// First, we find the permutation from s to t.
	std::map<int, set<int>> pos;
	vector<Node*> ptr_t_to_s(n);
	vector<int> perm(n);
	/*
	for (int i = 0; i < n; i++)
	{
		if (pos.find(t[i]) == pos.end()) pos[t[i]] = set<int>();
		pos[t[i]].insert(i);
	}
	for (int i = 0; i < n; i++)
	{
		if (pos.find(s[i]) == pos.end() || pos[s[i]].empty()) return !printf("impossible\n");
		int j = *pos[s[i]].begin();
		pos[s[i]].erase(j);
		perm[i] = j;

		ptr_t_to_s[j] = new Node(s[i]);
		merge(root, root, ptr_t_to_s[j]);
	}
	//*/
	//*
	// This is the piece of code above, but with the additional assumption that t is 1, 2, ..., n.
	for (int i = 0; i < n; i++)
	{
		perm[i] = s[i]-1;

		ptr_t_to_s[s[i]-1] = new Node(s[i]);
		merge(root, root, ptr_t_to_s[s[i]-1]);
	}
	//*/

	// Then if k is even, the answer depends on the signature of the permutation.
	// If the signature is -1, then it is impossible.
	if (k % 2 == 0)
	{
		bool signature = 0; // 0 for +1, 1 for -1
		vector<bool> visited(n, false);
		for (int i = 0; i < n; i++)
		{
			if (visited[i]) continue;
			int cycle_length = 0;
			int j = i;
			while (!visited[j])
			{
				visited[j] = true;
				j = perm[j];
				cycle_length++;
			}
			if (cycle_length % 2 == 0) signature = !signature;
		}
		if (signature) return !printf("impossible\n");
	}

	// Invariant: All elements after last_of_bad are in good positions and fixed.
	// Stage 1: elements in [2k-1, n-1]
	for (int j = n-1; j >= 2*k-1; j--)
	{
		int i = find_index(ptr_t_to_s[j]) + size(ptr_t_to_s[j]->left);

		if (i < k-1)
		{
			// If i < k-1, we cannot take a subarray of length k for which node is the last element.
			// So we move [0, k-1] to between 2k-2 and 2k-1.
			operation(0, 2*k-2);
			operation(i, j);
		}
		else if(i != j)
		{
			// Now we have i >= k-1, it means we can take a subarray of length k for which node is the last element.
			// Then we can rotate this subarray to move node to the last of current array.
			operation(i-k+1, j);
		}
	}

	// Stage 2: elements in [k, 2k-2]
	for (int j = min(n-1, 2*k-2); j >= k+2; j--)
	{
		int i = find_index(ptr_t_to_s[j]) + size(ptr_t_to_s[j]->left);
		if (i < k-1)
		{
			// If i < k-1, we cannot take a subarray of length k for which node is the last element.
			// The difference with the previous stage is that now we cannot move [0, k-1] to between 2k-2 and 2k-1,
			// because we already fixed the elements after 2k-1.
			// Thus we have to rotate manually to move node k-1.
			for (int x = 0; x < k-1-i; x++)
			{
				operation(0, k);
			}

			// Now the node is at k-1
			operation(0, j);
		}
		else if(i != j)
		{
			// Now we have i >= k-1, it means we can take a subarray of length k for which node is the last element.
			// Then we can rotate this subarray to move node to the last of current array.
			operation(i-k+1, j);
		}
	}

	// Stage 3: elements in [0, k+1]
	// First rotate to the left, so that 1 is at the front
	int i = find_index(ptr_t_to_s[0]) + size(ptr_t_to_s[0]->left);
	for (int x = 0; x < i; x++)
	{
		operation(1, -1);
	}
	for (int j = 1; j < k; j++)
	{
		// Invariant : the prefix [0...j-1] is precisely 1, 2, ..., j
		int i = find_index(ptr_t_to_s[j]) + size(ptr_t_to_s[j]->left);
		if (i < k+1)
		{

			if (i == k)
			{
				// Now the element j at k. Since we want to keep the prefix, if we take the prefix [0...k-1], it won't include the element j.
				// The trick is then to do one rotation to the right, so then it is j+1 1 2 ... j ... (k) (k+1)
				operation(0, k);
				// Then we do two rotations to the right on [1...k+1] to break the distance. Then we move it back.
				operation(1, k+1);
				operation(1, k+1);
				operation(2, -1);
				// Now it we should have 1 2 ... j ... something ... j+1 (k) (k+1)
				operation(1, k+1);
			}
			// Rotate to the right until this node is at k+1
			if (i < k)
			{
				// First rotate to the right until it reaches k
				for (int x = i; x < k; x++)
				{
					operation(0, k);
				}
				// Now it is at k, we move it to k+1
				operation(1, k+1);
			}
		}
		int end_idx_of_good_pref = find_index(ptr_t_to_s[j-1]) + size(ptr_t_to_s[j-1]->left);
		for (int x = end_idx_of_good_pref; x < k; x++)
		{
			operation(0, k);
		}

		// preserve invariant
		for (int x = 0; x <= j; x++)
		{
			operation(1, k+1);
		}
		operation(1, -1);
	}
	i = find_index(ptr_t_to_s[k]) + size(ptr_t_to_s[k]->left);
	if (i == k+1)
	{
		for (int x = 0; x < k/2; x++)
		{
			operation(2, -1);
		}

		operation(2, 1);
		operation(1, -1);
		operation(1, -1);
	}
	printf("%d\n", ans.size());
	while(!ans.empty()){
		printf("%d %d\n", ans.front().first, ans.front().second);
		ans.pop();
	}
}
