import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

// java version of paul.cpp
public class SquirrelChrisPaul {
	public static void main(String[] args) {

		Scanner sc = new Scanner(System.in);

		int n = sc.nextInt();
		int s = sc.nextInt() - 1;
		int h = sc.nextInt() - 1;
		int m = sc.nextInt() - 1;

		ArrayList<Integer>[] graph = new ArrayList[n];
		for (int i = 1; i < n; i++) {

			int a = sc.nextInt() - 1;
			int b = sc.nextInt() - 1;

			if (graph[a] == null) {
				graph[a] = new ArrayList<>();
			}
			if (graph[b] == null) {
				graph[b] = new ArrayList<>();
			}
			graph[a].add(b);
			graph[b].add(a);
		}

		int[] deg = new int[n];

		Queue<Integer> q = new LinkedList<Integer>();
		for (int i = 0; i < n; i++) {
			deg[i] = graph[i].size();
			if (deg[i] == 1)
				q.add(i);
		}

		// leaf nodes have height 0
		// a node has height k if it becomes a leaf after removing all nodes of
		// height < k
		int[] height = new int[n]; // height
		int c1 = 0, c2 = 0; // centers = nodes of maximal height, at most 2
		while (!q.isEmpty()) {
			int i = q.poll();

			c1 = c2;
			c2 = i;

			for (int j : graph[i]) {
				deg[j]--;
				if (deg[j] == 1) {
					height[j] = height[i] + 1;
					q.add(j);
				}
			}
		}

		// the answer is the maximal height among the reachable nodes, plus 1
		// (the strategy of the squirrel is to always move to the "highest"
		// node)

		boolean[] reach = new boolean[n];
		q.add(s);
		int hmax = 0; // maximal reachable height
		while (!q.isEmpty()) {
			int i = q.poll();
			if (i == h || i == m) {
				continue;
			}
			reach[i] = true;
			hmax = Math.max(hmax, height[i]);
			for (int j : graph[i]) {
				if (!reach[j]) {
					q.add(j);
				}
			}
		}

		// special case: need an extra turn if there are two centers
		// and squirrel can reach both
		if (height[c1] == height[c2] && reach[c1] && reach[c2])
			hmax++;

		System.out.println(hmax + 1);
	}
}
