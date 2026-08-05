// Author: Stefan Toman

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashSet;
import java.util.PriorityQueue;

public class Stefan {

    public static void main(String[] args) throws IOException {
        //read input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(r.readLine());
        Node[][] connections = new Node[n][n];
        int[] processingTime = new int[n];
        for (int i = 0; i < n; i++) {
            String[] tmp = r.readLine().split(" ");
            int m = Integer.parseInt(tmp[0]);
            int t = Integer.parseInt(tmp[1]);
            processingTime[i] = t;
            for (int j = 0; j < m; j++) {
                tmp = r.readLine().split(" ");
                int s = Integer.parseInt(tmp[0]);
                int x = Integer.parseInt(tmp[1]) - 1;
                HashSet<Integer> forbidden = new HashSet<>();
                for (int k = 0; k < s; k++) {
                    forbidden.add(Integer.parseInt(tmp[k + 2]) - 1);
                }
                connections[i][x] = new Node(i, x, forbidden);
            }
        }

        //initialize Dijkstra
        PriorityQueue<Node> active = new PriorityQueue<>();
        Node source = new Node(-1, 0, new HashSet<Integer>());
        active.add(source);
        source.distance = 0;

        while (!active.isEmpty()) {
            Node c = active.poll();

            if (c.target == n - 1) {
                System.out.println(c.distance + processingTime[n - 1]);
                System.exit(0);
            }

            for (int i = 0; i < n; i++) {
                Node next = connections[c.target][i];
                if (next != null && !next.forbiddenSources.contains(c.source)) {
                    if (next.distance > processingTime[c.target] + c.distance) {
                        next.distance = processingTime[c.target] + c.distance;
                        if (active.contains(next)) {
                            active.remove(next);
                        }
                        active.add(next);
                    }
                }
            }
        }

        System.out.println("impossible");
    }

    public static class Node implements Comparable<Node> {

        public int distance;
        //server ids that are not served by this connection if the predecessor is contained
        public HashSet<Integer> forbiddenSources;
        //the server id fo the start of this connection
        public int source, target;

        public Node(int source, int target, HashSet<Integer> forbiddenSources) {
            super();
            this.forbiddenSources = forbiddenSources;
            distance = Integer.MAX_VALUE;
            this.source = source;
            this.target = target;
        }

        @Override
        public int compareTo(Node o) {
            return distance - o.distance;
        }
    }

}
