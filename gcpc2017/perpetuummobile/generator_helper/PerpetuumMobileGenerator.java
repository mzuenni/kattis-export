import java.util.Random;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collections;

class WeightedArc {
    public int start;
    public int target;
    public double cost;

    public WeightedArc(int start, int target, double cost) {
        this.start = start;
        this.target = target;
        this.cost = cost;
    }

	@Override
	public String toString() {
		return String.format("%d %d %.4f", start+1, target+1, cost);
	}
}

public class PerpetuumMobileGenerator {
	public static double randomWeight(Random r, double max) {
		double c = r.nextDouble() * max;
        c = Math.floor(c * 10000) / 10000;
		c = Math.max(c,0.0001);
		return c;
   }
   
   public static void main(String[] args) {
        final double maxCycleProductAdmissable = 0.9;
	final double minCycleProductInadmissable = 1.1;
        Scanner sc = new Scanner(System.in);
        Random r = new Random(sc.nextLong());
        int minN = sc.nextInt();
        int maxN = sc.nextInt();
        int n = minN + r.nextInt(maxN - minN + 1);
        int m = 5 * (minN + r.nextInt(maxN - minN + 1));
        System.out.println(n + " " + m);
        
        int type = 1;
        if (sc.hasNext()) {
            type = sc.nextInt();
        }
        
        if (type == 1) {
            ArrayList<ArrayList<WeightedArc>> adj;
            adj = generateValidGraphInstance(n, m, maxCycleProductAdmissable, minCycleProductInadmissable,  r);
            for (int a = 0; a < n; a++) {
                for (WeightedArc e : adj.get(a)) {
                    System.out.println(e); //(a + 1) + " " + (e.target + 1) + " " + e.cost);
                }
            }
        } else if (type == 2 || type == 3) {
            ArrayList<WeightedArc> adj;
            adj = generateDag(n, m, r, type == 3);
            Collections.shuffle(adj);
            for (WeightedArc e : adj) {
                System.out.println(e); //(e.start + 1) + " " + (e.target + 1) + " " + e.cost);
            }
        } else if (type == 4 || type == 5) {
            ArrayList<WeightedArc> adj;
            adj = generateLine(n, m, r, type == 4);
            Collections.shuffle(adj);
            for (WeightedArc e : adj) {
                System.out.println(e); //(e.start + 1) + " " + (e.target + 1) + " " + e.cost);
            }
        }
        sc.close();
    }
    
    private static ArrayList<WeightedArc> generateLine(int n, int m, Random r, boolean forwards) {
        ArrayList<WeightedArc> adj = new ArrayList<WeightedArc>(n);
        if (forwards) {
            for (int i = 0; i < n - 1; i++) {
                double c = 1.001;
                adj.add(new WeightedArc(i, i + 1, c));
            }
        } else {
            for (int i = 1; i < n; i++) {
                double c = 1.001;
                adj.add(new WeightedArc(i, i - 1, c));
            }
        }
        for (int j = n-1; j < m; j++) {
            int b = r.nextInt(n - 1);
            int a = roll(r, b + 1, n - 1);
            double c = randomWeight(r,5.0);
            adj.add(new WeightedArc(a, b, c));
        }
        return adj;
    }

    private static ArrayList<WeightedArc> generateDag(int n, int m, Random r, boolean selfloops) {
        ArrayList<WeightedArc> adj = new ArrayList<WeightedArc>(n);
        for (int j = 0; j < m; j++) {
            int a = r.nextInt(n - 1);
            int b = roll(r, selfloops? a : a + 1, n - 1);
            
            double c = randomWeight(r,5.0);
            adj.add(new WeightedArc(a, b, c));
        }
        return adj;
    }
    public static int roll(Random r, int min, int max) {
        return min + r.nextInt(max - min + 1);
    }

    public static ArrayList<ArrayList<WeightedArc>> generateValidGraphInstance(int n, int m, double maxCycleProductAdmissable, double minCycleProductInadmissable, 
            Random r) {
	boolean admissable = r.nextBoolean();
        ArrayList<ArrayList<WeightedArc>> adj;
        double smallestCycleLength = 0.0;
        do {
            /* Generate random graph */
            adj = new ArrayList<ArrayList<WeightedArc>>(n);
            for (int i = 0; i < n; i++) {
                adj.add(new ArrayList<WeightedArc>());
            }
            for (int j = 0; j < m; j++) {
                int a = r.nextInt(n);
                int b = r.nextInt(n);
		double c = 0.0;
		int k = roll(r, 0, 50);
		if(!admissable || k == 1){
			c = randomWeight(r,5.0);
		}
		else{
			c = randomWeight(r,0.6);
		}
                c = Math.floor(c * 10000) / 10000;
                adj.get(a).add(new WeightedArc(a, b, c));
            }
            /*
             * Test whether graph satisfies constraints
             */
            double[][] dist = new double[n][n];
            for (int a = 0; a < n; a++) {
                for (int b = 0; b < n; b++) {
                    if (a == b) {
                        dist[a][b] = Double.POSITIVE_INFINITY;
                    } else {
                        dist[a][b] = Double.POSITIVE_INFINITY;
                    }

                }
            }
            for (int a = 0; a < n; a++) {
                for (WeightedArc e : adj.get(a)) {
                    int b = e.target;
                    double c = -Math.log(e.cost);
                    if (dist[a][b] > c) {
                        dist[a][b] = c;
                    }
                }
            }
            for (int k = 0; k < n; k++) {
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        if (dist[i][j] > dist[i][k] + dist[k][j]) {
                            dist[i][j] = dist[i][k] + dist[k][j];
                        }
                    }
                }
            }
            smallestCycleLength = dist[0][0];
            for (int a = 0; a < n; a++) {
                if (dist[a][a] < smallestCycleLength) {
                    smallestCycleLength = dist[a][a];
                }
            }

        } while ((admissable && smallestCycleLength <= -Math.log(maxCycleProductAdmissable)) || 
                 (!admissable && smallestCycleLength >= -Math.log(minCycleProductInadmissable)));

        return adj;
    }
}
