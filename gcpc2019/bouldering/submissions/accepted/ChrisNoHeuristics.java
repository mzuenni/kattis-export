import java.awt.*;
import java.util.ArrayList;
import java.util.Collections;
import java.util.PriorityQueue;
import java.util.Scanner;

// Solution for Bouldering by Christian Müller
public class ChrisNoHeuristics {

    static class Dist implements Comparable<Dist> {
        int node;
        double dist;
        int stam;

        public Dist(int node, double dist, int stam) {
            this.node = node;
            this.dist = dist;
            this.stam = stam;
        }

        @Override
        public int compareTo(Dist dist) {
            return Double.compare(this.dist, dist.dist);
        }
    }

    public static void main(String[] args) {

        var sc = new Scanner(System.in);

        var maxy = sc.nextInt() - 1;
        var maxx = sc.nextInt() - 1;

        var r = sc.nextInt();
        var s = sc.nextInt() + 1;

        s = Math.min(s, (maxy-1) * (maxx+1) * 9 + 19);

        ArrayList<ArrayList<Integer>> graph = new ArrayList<>();
        var points = new ArrayList<Point>();
        var ss = new ArrayList<Integer>();
        sc.nextLine(); // skip rest of line

        for (var y = 0; y <= maxy; y++) {
            var line = sc.nextLine().toCharArray();
            for (var x = 0; x <= maxx; x++) {
                if (line[x] != '.') {
                    var si = Integer.parseInt(Character.toString(line[x]));
                    graph.add(new ArrayList<>());
                    points.add(new Point(x, maxy - y));
                    ss.add(si);
                }
            }
        }

        var n = graph.size();
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                if (points.get(i).distance(points.get(j)) <= r) {
                    graph.get(i).add(j);
                    graph.get(j).add(i);
                }
            }
        }

        PriorityQueue<Dist> pq = new PriorityQueue<>();
        double[][] dists = new double[n][s];
        for (int i = 0; i < n; i ++) {
            for (int j = 0; j < s; j++) {
                dists[i][j] = Double.MAX_VALUE;
            }
        }
        int[][] prev = new int[n][s];
        boolean[][] visited = new boolean[n][s];
        int ymax = -1;
        int finindex = -1;
        int ymin = Integer.MAX_VALUE;
        int startindex = -1;

        for (int i = 0; i < n; i++) {
            int y = points.get(i).y;
            // if (y <= r) {
            //     pq.add(new Dist(i, y, ss.get(i)));
            //     dists[i][ss.get(i)] = y;
            // }
            if (y > ymax) {
                ymax = y;
                finindex = i;
            }
            if (y < ymin) {
                ymin = y;
                startindex = i;
            }
        }

        if (ss.get(startindex) < s) {
            pq.add(new Dist(startindex, 0, ss.get(startindex)));
            dists[startindex][ss.get(startindex)] = 0;
        }

        while(!pq.isEmpty()) {
            Dist dist = pq.poll();
            if (visited[dist.node][dist.stam]) {
                continue;
            }
            visited[dist.node][dist.stam] = true;
            for (var out : graph.get(dist.node)) {
                var newstam = dist.stam + ss.get(out);
                if (newstam < s && !visited[out][newstam]) {
                    var newdist = dist.dist + points.get(dist.node).distance(points.get(out));
                    if (newdist < dists[out][newstam]) {
                        dists[out][newstam] = newdist;
                        prev[out][newstam] = dist.node;
                        pq.add(new Dist(out, newdist, newstam));
                    }
                }
            }
        }

        var mindist = Double.MAX_VALUE;
        var minstam = Integer.MAX_VALUE;
        for (int i = 0; i < s; i++) {
            if (dists[finindex][i] < mindist) {
                mindist = dists[finindex][i];
                minstam = i;
            }
        }

        if (minstam == Integer.MAX_VALUE) {
            System.out.println("impossible");
        } else {
            System.out.println(mindist);

            // print path
            // int node = finindex;
            // int stam = minstam;
            // ArrayList<Integer> path = new ArrayList<>();
            // path.add(finindex);
            // while (node != startindex) {
            //     var newnode = prev[node][stam];
            //     stam -= ss.get(node);
            //     node = newnode;
            //     path.add(newnode);
            // }
            // Collections.reverse(path);

            // System.out.println("Used " + minstam + " stamina to reach target.");
            // System.out.println("Went via: ");
            // for (var i : path) {
            //     System.out.println("Node " + i + " at " + points.get(i).toString());
            // }
        }
    }

}
