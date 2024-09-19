import java.util.*;

public class Paul {
	static boolean isVowel(char c) {
		return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
	}

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		String word = sc.next();

		int index = word.length() - 1;
		while (!isVowel(word.charAt(index))) {
			index--;
		}

		System.out.println(word.substring(0,index+1) + "ntry");
	}
}
