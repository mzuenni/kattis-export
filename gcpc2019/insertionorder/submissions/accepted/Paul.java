import java.util.*;

public class Paul {
	static int offset = 0;
	
	static class Node {
		int inOrder;
		Node left, right;

		void traverse() {
			if (left != null) left.traverse();
			inOrder = ++offset;
			if (right != null) right.traverse();
		}
	}

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt(), k = sc.nextInt();

		if (k < 20 && (1 << k) <= n) {
			System.out.println("impossible");
			return;
		}
		
		Node[] nodes = new Node[n];
		for (int i = n-1; i >= 0; i--) {
			nodes[i] = new Node();
			if (2*i+1 < n) nodes[i].left = nodes[2*i+1];
			if (2*i+2 < n) nodes[i].right = nodes[2*i+2];
		}
		
		Node leftMost = nodes[0];
		int depth = 1;
		while (leftMost.left != null) {
			leftMost = leftMost.left;
			depth++;
		}
		
		for (int i = n-1; depth < k; i--) {
			if ((i & (i+1)) == 0) continue;
			System.err.println(i);
			Node cur = nodes[i];
			Node parent = nodes[(i-1)/2];
			if (i%2 == 0) {
				parent.right = null;
			} else {
				parent.left = null;
			}
			leftMost.left = cur;
			leftMost = cur;
			depth++;
		}

		nodes[0].traverse();
		
		for (int i = 0; i < n; i++) {
			if (i > 0) System.out.print(" ");
			System.out.print(nodes[i].inOrder);
		}
		System.out.println();
	}
}
