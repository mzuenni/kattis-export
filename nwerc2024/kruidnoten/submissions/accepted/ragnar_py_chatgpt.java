import java.util.*;
import java.io.*;

public class ragnar_py_chatgpt {
    static final long INF = (long) 1e15;
    static int n, m, k;
    static List<List<Pair>> g;

    static class Pair {
        int node;
        long weight;

        Pair(int node, long weight) {
            this.node = node;
            this.weight = weight;
        }
    }

    static class DistPair implements Comparable<DistPair> {
        long distance;
        int node;

        DistPair(long distance, int node) {
            this.distance = distance;
            this.node = node;
        }

        @Override
        public int compareTo(DistPair other) {
            return Long.compare(this.distance, other.distance);
        }
    }

    static long[] dijkstra(int start) {
        long[] dist = new long[n];
        Arrays.fill(dist, INF);
        dist[start] = 0;

        PriorityQueue<DistPair> pq = new PriorityQueue<>();
        pq.add(new DistPair(0, start));

        while (!pq.isEmpty()) {
            DistPair current = pq.poll();
            long d = current.distance;
            int u = current.node;

            if (d != dist[u]) continue;

            for (Pair edge : g.get(u)) {
                int v = edge.node;
                long weight = edge.weight;

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.add(new DistPair(dist[v], v));
                }
            }
        }
        return dist;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        n = Integer.parseInt(st.nextToken());
        m = Integer.parseInt(st.nextToken());
        k = Integer.parseInt(st.nextToken());

        g = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            g.add(new ArrayList<>());
        }

        for (int i = 0; i < m; i++) {
            st = new StringTokenizer(br.readLine());
            int iNode = Integer.parseInt(st.nextToken()) - 1;
            int jNode = Integer.parseInt(st.nextToken()) - 1;
            long length = Long.parseLong(st.nextToken());
            g.get(iNode).add(new Pair(jNode, length));
            g.get(jNode).add(new Pair(iNode, length));
        }

        int s = 0;
        int t = n - 1;

        long[] ds = dijkstra(s);
        long[] dt = dijkstra(t);

        List<SpecialPair> special = new ArrayList<>();
        for (int i = 0; i < k; i++) {
            st = new StringTokenizer(br.readLine());
            int index = Integer.parseInt(st.nextToken()) - 1;
            double probability = Double.parseDouble(st.nextToken());
            long distance = ds[index] + dt[index];
            special.add(new SpecialPair(distance, probability));
        }

        special.sort(Comparator.comparingLong(o -> o.distance));

        double ans = 0.0;
        double p = 1.0;
        for (SpecialPair sp : special) {
            if (sp.distance >= INF) break;

            ans += sp.distance * p * sp.probability;
            if (sp.probability == 1.0) {
                System.out.printf("%.10f%n", ans);
                return;
            }
            p *= (1.0 - sp.probability);
        }
        System.out.println("impossible");
    }

    static class SpecialPair {
        long distance;
        double probability;

        SpecialPair(long distance, double probability) {
            this.distance = distance;
            this.probability = probability;
        }
    }
}
