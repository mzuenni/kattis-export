import java.io.*;
import java.util.*;

public class mzuenni {

	static int bands, fans, lim;
	static ArrayList<Integer>[] adj;
	static int[] deg;

	static boolean remove(int i) {
		if (deg[i] <= 0) return false;
		if (i < bands) {
			return deg[i] < lim;
		} else {
			return 2 * deg[i] < adj[i].size();
		}
	}

	public static void main(String[] args) {
		Scanner s = new Scanner(System.in);
		bands = s.nextInt();
		fans = s.nextInt();
		lim = s.nextInt();

		adj = new ArrayList[bands+fans];
		for (int i = 0; i < bands+fans; i++) adj[i] = new ArrayList<>();

		for (int i = 0; i < fans; i++) {
			int k = s.nextInt();
			for (int j = 0; j < k; j++) {
				int b = s.nextInt();
				b--;
				adj[b].add(i+bands);
				adj[i+bands].add(b);
			}
		}

		deg = new int[bands+fans];
		for (int i = 0; i < bands+fans; i++) deg[i] = adj[i].size();

		ArrayDeque<Integer> todo = new ArrayDeque<>();
		for (int i = 0; i < bands+fans; i++) {
			if (remove(i)) {
				todo.addLast(i);
				deg[i] = 0;
			}
		}

		while (!todo.isEmpty()) {
			int c = todo.removeLast();
			for (int x : adj[c]) {
				deg[x]--;
				if (remove(x)) {
					todo.addLast(x);
					deg[x] = 0;
				}
			}
		}

		ArrayList<Integer> res = new ArrayList<>();
		for (int i = 0; i < bands; i++) {
			if (deg[i] > 0) res.add(i);
		}

		if (res.isEmpty()) {
			System.out.println("impossible");
		} else {
			System.out.println("possible");
			System.out.println(res.size());
			for (int x : res) {
				System.out.print(x+1);
				System.out.print(" ");
			}
			System.out.println();
		}
	}
}
