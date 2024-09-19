import java.util.*;

public class Paul {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int doors = sc.nextInt();
		int select = sc.nextInt();
		int open = sc.nextInt();

		int rem = doors - select - open;

		double sel_prob = 1.0/doors;
		double rem_prob = (double) (doors-select) / doors / rem;
	
		double res = 0;
		while (select --> 0) {
			if (rem-- > 0) res += rem_prob;
			else res += sel_prob;
		}
		System.out.format("%.20f\n", res);
	}
}
