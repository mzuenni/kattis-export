import java.util.Scanner;

public class yvonne {
	public static final int NOOP = 0;
	public static final int FLIP_H = 1;
	public static final int FLIP_V = 2;
	public static final int ROTATE = 3;

	static String replace(String s, char n[]) {
		char c[] = s.toCharArray();
		for (int i = 0; i < c.length; ++i) {
			switch (c[i]) {
			case 'b':
				c[i] = n[0];
				break;
			case 'd':
				c[i] = n[1];
				break;
			case 'p':
				c[i] = n[2];
				break;
			case 'q':
				c[i] = n[3];
				break;
			}
		}
		return new String(c);

	}
	
	public static void main(String args[]) {
		Scanner sc = new Scanner(System.in);

		String s = sc.next();
		String t = sc.next();

		int op = NOOP;
		for (char c: t.toCharArray()) {
			if (c == 'h') {
				switch (op) {
				case NOOP:
					op = FLIP_H;
					break;
				case FLIP_H:
					op = NOOP;
					break;
				case FLIP_V:
					op = ROTATE;
					break;
				case ROTATE:
					op = FLIP_V;
					break;
				}
			} else if (c == 'v') {
				switch (op) {
				case NOOP:
					op = FLIP_V;
					break;
				case FLIP_H:
					op = ROTATE;
					break;
				case FLIP_V:
					op = NOOP;
					break;
				case ROTATE:
					op = FLIP_H;
					break;
				}
			} else if (c == 'r') {
				switch (op) {
				case NOOP:
					op = ROTATE;
					break;
				case FLIP_H:
					op = FLIP_V;
					break;
				case FLIP_V:
					op = FLIP_H;
					break;
				case ROTATE:
					op = NOOP;
					break;
				}
			}
		}

		switch (op) {
		case NOOP:
			break;
		case FLIP_H:
			s = new StringBuilder(replace(s, new char[]{'d', 'b', 'q', 'p'})).reverse().toString();
			break;
		case FLIP_V:
			s = replace(s, new char[]{'p', 'q', 'b', 'd'});
			break;
		case ROTATE:
			s = new StringBuilder(replace(s, new char[]{'q', 'p', 'd', 'b'})).reverse().toString();
			break;
		}

		System.out.println(s);
	}
}
