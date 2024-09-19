import java.util.*;

public class jannik2 {
	static HashSet<String> go(HashSet<String> old) {
		HashSet<String> res = (HashSet<String>)old.clone();
		boolean ok = true;
		for (String k : old)
			for (int i = 0; i + 1 < k.length(); i++)
				if (k.charAt(i) == 's' && k.charAt(i+1) == 's')
					ok &= !res.add(k.substring(0, i) + 'B' + k.substring(i+2, k.length()));
		if (ok)
			return res;
		return go(res);
	}
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		String s = in.next().toLowerCase();
		HashSet<String> res = new HashSet<>();
		res.add(s);
		res = go(res);
		for (String k : res)
			System.out.println(k);
	}
}
