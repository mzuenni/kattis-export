import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;

public class jeroen_nosort {
	static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

	public static void main(String[] args) throws Exception {
		// Read input
		int n = Integer.valueOf(in.readLine());
		int[] nums = new int[n];
		String[] ps = in.readLine().split(" ");
		for(int i = 0; i < n; i++)
			nums[i] = Integer.valueOf(ps[i]);

		// Check which numbers have to be added to the next one
		boolean[] plus = new boolean[n-1];
		for(int i = 0; i < n; i++) {
			if(nums[i] == 1) {
				int before = i == 0 ? -1 : nums[i-1];
				int j = i;
				while(j < n && nums[j] == 1) j++;
				int after = j < n ? nums[j] : -1;
				int amount = j - i;
				int plusStart = i;
				if(amount % 2 == 1) {
					if(before == -1 && after == -1) {
						if(j > 1)
							plus[j-2] = true;
					} else if(before == -1 || (after != -1 && after < before)) {
						plus[j-1] = true;
					} else {
						plusStart = i + 1;
						plus[i-1] = true;
					}
				}
				for(int k = plusStart; k < j - 1; k += 2)
					plus[k] = true;
				i = j;
			}
		}

		// Print the resulting expression
		boolean inParens = false;
		StringBuilder res = new StringBuilder();
		for(int i = 0; i < n - 1; i++) {
			if(plus[i]) {
				if(!inParens)
					res.append('(');
				inParens = true;
				res.append(nums[i]);
				res.append('+');
			} else {
				res.append(nums[i]);
				if(inParens) res.append(')');
				inParens = false;
				res.append('*');
			}
		}
		res.append(nums[n-1]);
		if(inParens) res.append(')');
		System.out.println(res);
	}
}
