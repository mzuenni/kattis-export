/***
 * 	Author: Christian Müller,
 * 	written for the GCPC 2016
 */

import java.util.HashMap;
import java.util.LinkedList;
import java.util.Scanner;

public class MazeChristian {
	static class Node {
		HashMap<Character, LinkedList<Integer>> out = new HashMap<>();
	}
	static double EPS = 10e-6;

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);

		int n = sc.nextInt();
		int m = sc.nextInt();

		Node[] graph = new Node[n];
		for (int i = 0; i < n; i++) {
			graph[i] = new Node();
		}

		for (int i = 0; i < m; i++) {
			int a = sc.nextInt() - 1;
			int b = sc.nextInt() - 1;
			char l = sc.next().charAt(0);

			graph[a].out.putIfAbsent(l, new LinkedList<>());
			graph[a].out.get(l).add(b);
			graph[b].out.putIfAbsent(l, new LinkedList<>());
			graph[b].out.get(l).add(a);
		}
		char[] letters = sc.next().toCharArray();

		int start = 0;
		int finish = n - 1;

		double[] probs = new double[n];
		probs[start] = 100;

		for (int i = 0; i < letters.length; i++) {
			double[] newprobs = new double[n];
			
			for (int j = 0; j < probs.length; j++) {
				if (probs[j] > 0) {
					LinkedList<Integer> out = graph[j].out.get(letters[i]);
					if (out != null && j != finish) {
						// Go through door
						for (Integer e : out) {
							newprobs[e] = newprobs[e] + (probs[j] / out.size());
						}
					} else {
						// stay still
						newprobs[j] = newprobs[j] + probs[j];
					}
				}
			}

			probs = newprobs;
		}

		System.out.println(probs[finish]);

		sc.close();
	}
}
