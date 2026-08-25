
import java.util.Scanner;

public class KnapsackPhilipp {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		long k = sc.nextLong();
		int[] size = new int[n];
		int ggt = 0;
		for (int i = 0; i < size.length; i++) {
			size[i] = sc.nextInt();
			if (i == 0) {
				ggt = size[i];
			} else {
				ggt = euclid(ggt, size[i]);
			}
		}
		sc.close();
		if (k % ggt != 0) {
			System.out.println("impossible");
			return;
		}
		// arbitrary bound that is greater than the product of the two largest elements
		if (k >= 2000000) {
			System.out.println("possible");
			return;
		}
		// do brute force to find out if it is possible
		boolean[] reachable = new boolean[2000000];
		reachable[0] = true;
		for (int i = 0; i < n; i++) {
			int s = size[i];
			for (int j = 0; j < reachable.length; j++) {
				if (reachable[j] && j+s<reachable.length) {
					reachable[j+s]=true;
				}
			}
		}
		if (reachable[(int)k]) {
			System.out.println("possible");
		} else {
			System.out.println("impossible");
		}
	}

	public static int euclid(int i, int j) {
		if (j == 0) {
			return i;
		}
		return euclid(j, i % j);
	}
}
