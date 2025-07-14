import java.util.Scanner;

public class Yidi {
	public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        String op = sc.next();
        int n = sc.nextInt();
        String s = sc.next();

        if (op.charAt(0) == 'E') {
            int b = 0;
            while (b < n && s.charAt(b) != '1') b++;
            if (b == n) {
                System.out.println(s);
            } else {
                StringBuilder ans = new StringBuilder();
                for (int i=0; i<=b; i++) ans.append('2');
                for (int i=b+1; i<n; i++) ans.append(s.charAt(i));
                System.out.println(ans);
            }
        } else {
            int b = 0;
            for (int i=1; i<n; i++) {
                if (s.charAt(i-1) != '2' && s.charAt(i) == '2') b = i;
            }

            if (s.charAt(b) != '2') {
                System.out.println(s);
            } else {
                StringBuilder ans = new StringBuilder();
                for (int i=0; i<n; i++) {
                    if (s.charAt((b+i)%n) != '2') {
                        ans.append(s.charAt((b+i)%n));
                    } else {
                        if (i > 0) {
                            ans.setCharAt(i-1, '0');
                        }
                        ans.append('1');
                    }
                }
                System.out.println(ans);
            }
        }
	}
}
