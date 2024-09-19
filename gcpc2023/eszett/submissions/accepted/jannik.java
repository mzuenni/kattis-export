import java.util.*;

public class jannik {
	static void go(String cur, int i, String s) {
		if (i >= s.length()) {
			System.out.println(cur);
			return;
		}
		if (s.charAt(i) == 'S' && i + 1 < s.length() && s.charAt(i+1) == 'S') {
			go(cur + "B", i+2, s);
		}
		go(cur + (char)(s.charAt(i) - 'A' + 'a'), i+1, s);
	}
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		String s = in.next();
		go("", 0, s);
	}
}
