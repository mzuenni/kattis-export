import java.util.*;

public class andreas {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int k = sc.nextInt();
        System.out.println(("a".repeat(k) + "bcd".repeat(n)).substring(0, n));
    }
}
