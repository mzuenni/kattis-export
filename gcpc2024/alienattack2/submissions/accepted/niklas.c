#include <stdio.h>
#include <stdlib.h>

// Union-Find Data Structure
typedef struct uf {
    int n;
    int *parents;
    int *size;
} uf;

void init_unionfind(uf *uf, int n) {
    uf->n = n;
    uf->parents = (int *)malloc(n * sizeof(int));
    uf->size = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        uf->parents[i] = i;
        uf->size[i] = 1;
    }
}

int find(uf *d, int x) {
    if (x != d->parents[x])
        d->parents[x] = find(d, d->parents[x]);
    return d->parents[x];
}

void unite(uf *d, int x, int y) {
    x = find(d, x);
    y = find(d, y);
    if (x == y)
        return;
    if (d->size[x] < d->size[y]) {
        int temp = x;
        x = y;
        y = temp;
    }
    d->parents[y] = x;
    d->size[x] += d->size[y];
}

int main() {
    // n humans & m friendships.
    int n, m;
    scanf("%d %d", &n, &m);

    uf uf;
    init_unionfind(&uf, n);

    // Read friendships.
    while (m--) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--, b--;

        // Merge components of a and b, if they are friends. This way, we can
        // determine the size of the component containing a or b at the end.
        unite(&uf, a, b);
    }

    int max_size = 0;
    for (int i = 0; i < n; i++) {
        if (uf.size[i] > max_size)
            max_size = uf.size[i];
    }

    // Print and free.
    free(uf.parents);
    free(uf.size);
    printf("%d\n", max_size);
    return 0;
}
