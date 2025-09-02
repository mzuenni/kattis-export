import java.util.*;

public class Paul {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		while (sc.hasNext()) {
			String pos;
			switch(sc.next().charAt(0)) {
				case 'I': pos = "1 1"; break;
				case 'J':
				case 'L': pos = "2 2"; break;
				case 'O': pos = "0 5"; break;
				case 'S': pos = "1 7"; break;
				case 'T':
				case 'Z': pos = "1 9"; break;
				default: return;
			}
			System.out.println(pos);
		}
	}
}
