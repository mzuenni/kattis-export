import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;

public class jeroen {
	static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

	public static void main(String[] args) throws Exception {
		// Read input
		int n = Integer.valueOf(in.readLine());
		int[] nums = new int[n];
		String[] ps = in.readLine().split(" ");
		for(int i = 0; i < n; i++)
			nums[i] = Integer.valueOf(ps[i]);

		// Split into 1, 2 and rest
		ArrayList<Integer> rest = new ArrayList<Integer>();
		int ones = 0;
		int twos = 0;
		for(int i = 0; i < n; i++) {
			switch(nums[i]) {
			case 1:
				ones++;
				break;
			case 2:
				twos++;
				break;
			default:
				rest.add(nums[i]);
			}
		}
		int trinity = Math.min(ones, twos);
		ones -= trinity;
		twos -= trinity;
		while(twos-- > 0)
			rest.add(2);
		Collections.sort(rest);

		// For the remaining ones, do them in pairs of three
		// but be careful with the last few
		ArrayList<String> parts = new ArrayList<String>();
		while(ones > 4 || ones == 3) {
			parts.add("(1+1+1)");
			ones -= 3;
		}

		while(ones > 0 && ones % 2 == 0) {
			parts.add("(1+1)");
			ones -= 2;
		}
		if(ones == 1) {
			if(trinity > 0) {
				trinity--;
				rest.add(2);
				parts.add("(1+1)");
			} else if(rest.size() > 0) {
				int x = rest.remove(0);
				parts.add("(1+" + x + ")");
			} else { // just a single 1...
				parts.add("1");
			}
		}
		while(trinity-- > 0)
			parts.add("(1+2)");
		for(int x : rest)
			parts.add(String.valueOf(x));

		// Print the output in a slow way
		boolean first = true;
		for(String p : parts) {
			if(!first) System.out.print('*');
			first = false;
			System.out.print(p);
		}
		System.out.println();
	}
}
