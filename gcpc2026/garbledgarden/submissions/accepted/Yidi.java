import java.util.*;

public class Yidi {
    public static ArrayList<Integer> g[];
    public static ArrayList<Integer> cycle;

	public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int n = sc.nextInt();
        int[] a = new int[n];
        for (int i=0; i<n; i++) a[i] = sc.nextInt() - 1;

        int[] a2 = a.clone();
        Arrays.sort(a2);
        g = new ArrayList[n];
        for (int i=0; i<n; i++) g[i] = new ArrayList<Integer>();
        for (int it=0; it<2; it++) {
            int[] rev = new int[n];
            for (int i=0; i<n; i++) if (a[i] != a2[i]) {
                g[a[i]].add(a2[i]);
                g[a[i]].add(i);
                rev[a[i]] = i;
            }

            ArrayList<Integer> comps = new ArrayList<Integer>();
            cycle = new ArrayList<Integer>();
            for (int i=0; i<n; i++) if (!g[i].isEmpty()) {
                comps.add(rev[i]);
                euler(i);
            }
            Collections.reverse(cycle);

            if (comps.isEmpty()) {
                System.out.println(0);
                System.exit(0);
            }

            if (comps.size() == 1) {
                if (it == 0) {
                    System.out.println(1);
                }
                System.out.println(cycle.size());
                for (int e : cycle) System.out.print((e+1) + " ");
                System.out.println();
                System.exit(0);
            }

            int[] a3 = a.clone();
            for (int i=0; i<comps.size(); i++) {
                a[comps.get(i)] = a3[comps.get((i+1) % comps.size())];
            }

            System.out.println(2);
            System.out.println(comps.size());
            for (int e : comps) System.out.print((e+1) + " ");
            System.out.println();
        }
	}

    public static void euler(int u) {
        while (!g[u].isEmpty()) {
            int v = g[u].remove(0); // peak efficiency
            int x = g[u].remove(0);
            euler(v);
            cycle.add(x);
        }
    }
}
