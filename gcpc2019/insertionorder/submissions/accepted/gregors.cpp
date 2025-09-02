#include <iostream>
#include <cmath>
using namespace std;

const int MAX_N = 2e5+1;
struct Node {int p,l,r;};
Node tree[MAX_N];

int bintree(int p, int l, int r)
{
    if (l > r) return 0;
    int m = (l + r) / 2;
    tree[m].p = p;
    tree[m].l = bintree(m,l,m-1);
    tree[m].r = bintree(m,m+1,r);
    return m;
}

int rotate(int &root, int x)
{
    while (tree[x].l == 0)
        x = tree[x].r;
    int l = tree[x].l;
    int p = tree[x].p;
    if (p == 0) root = l;
    tree[p].r = l;
    tree[l].p = p;
    tree[x].p = l;
    tree[x].l = tree[l].r;
    tree[l].r = x;
    return l;
}

void printNode(int x)
{
    if (x == 0) return;
    cout << x << " ";
    printNode(tree[x].l);
    printNode(tree[x].r);
}

int main()
{
    int n,k;
    cin >> n >> k;
    int h = 1 + log2(n);
    if (h > k)
    {
        cout << "impossible" << endl;
        return 0;
    }
    int root = bintree(0, 1, n);
    int z = root;
    while (h++ < k)
        z = rotate(root, z);
    printNode(root);
    cout << endl;
}
