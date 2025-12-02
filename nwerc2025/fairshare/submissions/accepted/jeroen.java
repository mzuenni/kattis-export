import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;

public class jeroen {
	static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

	public static void main(String[] args) throws Exception {
		// Read input
		int n = Integer.valueOf(in.readLine());
		int[] a = new int[n];
		int[] b = new int[n];
		for (int i = 0; i < n; i++) {
			String[] ps = in.readLine().split(" ");
			a[i] = Integer.valueOf(ps[0]);
			b[i] = Integer.valueOf(ps[1]);
		}

		// Find out the totals
		int total_actual = 0;
		int total_need = 0;
		for (int i = 0; i < n; i++) {
			total_actual += a[i];
			total_need += b[i];
		}

		// Find a person to settle
		int person = -1;
		int diff = 0;
		for (int i = 0; i < n; i++) {
			// Check if this person can settle the bill
			int need_pay = total_need - (total_actual - a[i]);
			if (need_pay <= b[i]) {
				// Check if the difference is smaller than earlier found
				int thisdiff = b[i] - need_pay;
				if (person == -1 || thisdiff < diff) {
					person = i;
					diff = thisdiff;
				}
			}
		}

		System.out.println(person >= 0 ? (person + 1) : "impossible");
	}
}
