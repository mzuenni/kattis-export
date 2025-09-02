import java.util.*;

public class HeliskiingGenerator {

    static class WeightedArc {
        public int start, target, cost;

        public WeightedArc(int start, int target, int cost) {
            this.start = start;
            this.target = target;
            this.cost = cost;
        }

        @Override
        public String toString() {
            return String.format("%d %d %d", start+1, target+1, cost);
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        long seed = sc.nextLong();

        int nMin = sc.nextInt();
        int nMax = sc.nextInt();
        int mMin = sc.nextInt();
        int mMax = sc.nextInt();
        int cMin = sc.nextInt();
        int cMax = sc.nextInt();
        int type = sc.nextInt();
        sc.close();

        Random r = new Random(seed);
        ArrayList<WeightedArc> graph = null;
        int n = roll(r, nMin, nMax);
        int m = roll(r, mMin, mMax);

        switch (type) {
            case 1:
                graph = generateDag(n, m, r, false, cMin, cMax);
                break;
            case 2:
            case 3:
                graph = generateLine(n, m,r,type == 2, cMin, cMax);
                break;
        }
        Collections.shuffle(graph);

        System.out.println(n + " " + m);
        for (WeightedArc e : graph) {
            System.out.println(e); //(e.start + 1) + " " + (e.target + 1) + " " + e.cost);
        }
    }

    /**
     * Rolls a random number between min and max (inclusively)
     */
    public static int roll(Random r, int min, int max) {
        return min + r.nextInt(max - min + 1);
    }

    private static ArrayList<WeightedArc> generateDag(int n, int m, Random r, boolean selfloops, int cMin, int cMax) {
        ArrayList<WeightedArc> adj = new ArrayList<>(n);
        for (int j = 0; j < m; j++) {
            int a = r.nextInt(n - 1);
            int b = roll(r, selfloops? a : a + 1, n - 1);

            int c = roll(r, cMin, cMax);
            adj.add(new WeightedArc(a, b, c));
        }
        return adj;
    }

    private static ArrayList<WeightedArc> generateLine(int n, int m, Random r, boolean forwards, int cMin, int cMax) {
        ArrayList<WeightedArc> adj = new ArrayList<>(n);
        if (forwards) {
            for (int i = 0; i < n - 1; i++) {
                int c = roll(r, cMin, cMax);
                adj.add(new WeightedArc(i, i + 1, c));
            }
        } else {
            for (int i = 1; i < n; i++) {
                int c = roll(r, cMin, cMax);
                adj.add(new WeightedArc(i, i - 1, c));
            }
        }
        for (int j = n-1; j < m; j++) {
            int a = r.nextInt(n - 1);
            int b = roll(r, a + 1, n - 1);
            int c = roll(r, cMin, cMax);
            if (forwards) {
                adj.add(new WeightedArc(a, b, c));
            } else {
                adj.add(new WeightedArc(b, a, c));
            }
        }
        return adj;
    }
}
