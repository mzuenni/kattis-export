import java.util.*;

public class Alex {
  public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		String s = sc.next();
		sc.close();
		char vowels[] = {'A', 'E', 'I', 'O', 'U', 'a', 'e', 'i', 'o', 'u'};
		int lastIndex = -1;
		for(char c : vowels) {
			lastIndex = Math.max(s.lastIndexOf(c), lastIndex);
		}
		System.out.println(s.substring(0,lastIndex + 1) + "ntry");
  }
}
