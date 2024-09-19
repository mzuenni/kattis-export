import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;

public class jeroen_fastio {
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
		StringBuilder ret = new StringBuilder();
		boolean first = true;
		while(ones > 4 || ones == 3) {
			if(!first) ret.append('*');
			first = false;
			ret.append("(1+1+1)");
			ones -= 3;
		}

		while(ones > 0 && ones % 2 == 0) {
			if(!first) ret.append('*');
			first = false;
			ret.append("(1+1)");
			ones -= 2;
		}
		if(ones == 1) {
			if(trinity > 0) {
				trinity--;
				rest.add(2);
				if(!first) ret.append('*');
				first = false;
				ret.append("(1+1)");
			} else if(rest.size() > 0) {
				int x = rest.remove(0);
				if(!first) ret.append('*');
				first = false;
				ret.append("(1+" + x + ")");
			} else { // just a single 1...
				if(!first) ret.append('*');
				first = false;
				ret.append("1");
			}
		}
		while(trinity-- > 0) {
			if(!first) ret.append('*');
			first = false;
			ret.append("(1+2)");
		}
		for(int x : rest) {
			if(!first) ret.append('*');
			first = false;
			ret.append(String.valueOf(x));
		}

		System.out.println(ret);
	}
}
