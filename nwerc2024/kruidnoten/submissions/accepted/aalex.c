#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 200000

typedef struct {
  int u, v;
  long long len;
} cycleway;

typedef struct {
  int v;
  double p;
} store;

int n, m, k;
cycleway cycleways[2 * MAX];
store stores[MAX];

int heap[MAX];
int hindex[MAX];
long long dist0[MAX], distn[MAX];

int cmp_cycleways(const void* a, const void* b) {
  const cycleway* cycleway_a = a;
  const cycleway* cycleway_b = b;
  return cycleway_a->u - cycleway_b->u;
}

int find_cycleways(int u) {
  int a = -1, b = m;
  while (b - a > 1) {
    int c = (a + b) / 2;
    if (cycleways[c].u < u) a = c;
    else b = c;
  }
  return b;
}

void shortest_paths(int src, long long dist[]) {
  memset(dist, -1, n * sizeof dist[0]);
  dist[src] = 0;
  heap[hindex[src] = 0] = src;
  for (int heaplen = 1; heaplen > 0; ) {
    int u = heap[0];
    heap[hindex[heap[heaplen - 1]] = 0] = heap[heaplen - 1];
    --heaplen;
    for (int i = 0, j; 2 * i < heaplen; i = j) {
      j = 2 * i;
      if (j + 1 < heaplen && dist[heap[j + 1]] < dist[heap[j]]) ++j;
      if (dist[heap[i]] <= dist[heap[j]]) break;

      int tmp = heap[i];
      heap[hindex[heap[j]] = i] = heap[j];
      heap[hindex[tmp] = j] = tmp;
    }

    for (int i = find_cycleways(u); i < m && cycleways[i].u == u; ++i) {
      int v = cycleways[i].v;
      long long d = dist[u] + cycleways[i].len;
      if (dist[v] < 0) {
        heap[hindex[v] = heaplen++] = v;
      } else if (dist[v] <= d) {
        continue;
      }

      dist[v] = d;
      for (int i = hindex[v]; i > 0 && d < dist[heap[i >> 1]]; i >>= 1) {
        int tmp = heap[i >> 1];
        heap[hindex[v] = i >> 1] = v;
        heap[hindex[tmp] = i] = tmp;
      }
    }
  }
}

int cmp_stores(const void* a, const void* b) {
  const store* store_a = a;
  const store* store_b = b;
  return (dist0[store_a->v] + distn[store_a->v])
       - (dist0[store_b->v] + distn[store_b->v]);
}

int main() {
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 0; i < m; ++i) {
    scanf("%d%d%lld", &cycleways[i].u, &cycleways[i].v, &cycleways[i].len);
    --cycleways[i].u;
    --cycleways[i].v;
  }
  int ok = 0;
  for (int i = 0; i < k; ++i) {
    scanf("%d%lf", &stores[i].v, &stores[i].p);
    --stores[i].v;
    ok = ok || stores[i].p == 1.0;
  }

  if (!ok) {
    printf("impossible\n");
    return 0;
  }

  for (int i = 0; i < m; ++i) {
    cycleways[m + i].u = cycleways[i].v;
    cycleways[m + i].v = cycleways[i].u;
    cycleways[m + i].len = cycleways[i].len;
  }
  m *= 2;
  qsort(cycleways, m, sizeof cycleways[0], cmp_cycleways);

  shortest_paths(0, dist0);
  shortest_paths(n - 1, distn);
  qsort(stores, k, sizeof stores[0], cmp_stores);

  long double result = 0.0;
  long double prob = 1.0;
  for (store* p = stores; p != stores + k; ++p) {
    result += (dist0[p->v] + distn[p->v]) * prob * p->p;
    prob *= 1.0 - p->p;
  }

  printf("%.10Lf\n", result);

  return 0;
}
