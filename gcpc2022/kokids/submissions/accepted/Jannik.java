import java.util.*;

public class Jannik {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt(), k = in.nextInt();
		String s = in.next();

		int fallen = 0;
		char last = 'R';
		for (int i = 0; i < n && fallen < k; i++) {
			if (last == s.charAt(i))
				fallen++;
			else
				last = s.charAt(i);
		}
		System.out.println(k-fallen);
	}
}
