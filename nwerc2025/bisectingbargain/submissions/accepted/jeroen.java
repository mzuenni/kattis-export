import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;

public class jeroen {
	// Not sure how to call "coins or notes"
	static final int[] moneys = {500, 200, 100, 50, 20, 10, 5, 2, 1};
	static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

	public static void main(String[] args) throws Exception {
		// Read input
		int x = Integer.valueOf(in.readLine());

		// Greedily pick the biggest coins
		int[] coins = new int[moneys.length];
		int total = 0;
		for (int i = 0; i < moneys.length; i++) {
			while (x - total >= moneys[i]) {
				coins[i]++;
				total += moneys[i];
			}
		}

		// Special case since we have no 1000 note, replace
		// two 500's by five 200's
		if (coins[0] >= 2 && coins[0] % 2 == 0 && coins[1] % 2 == 0) {
			coins[1] += 5 * (coins[0] / 2);
			coins[0] = 0;
		}

		// Check if we can make the target with a simple dp
		int target = x / 2;
		boolean[][] canmake = new boolean[moneys.length + 1][target + 1];
		canmake[0][0] = true;
		for (int j = 0; j < moneys.length; j++) {
			for (int i = 0; i <= target; i++) {
				if (!canmake[j][i])
					continue;
				canmake[j + 1][i] = true;
				for (int k = 1; k <= coins[j]; k++) {
					int result = k * moneys[j] + i;
					if(result <= target)
						canmake[j + 1][result] = true;
				}
			}
		}

		if (x % 2 == 0 && canmake[moneys.length][target]) {
			System.out.println("splittable");
			return;
		}

		int amount = 0;
		for(int i = 0; i < coins.length; i++)
			amount += coins[i];
		// System.out.println("unsplittable");
		System.out.println(amount);
		for(int i = 0; i < coins.length; i++)
			for(int j = 0; j < coins[i]; j++)
				System.out.print(moneys[i] + " ");
		System.out.println();
	}
}
