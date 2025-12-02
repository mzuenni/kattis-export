import java.util.*;

public class Paul {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int[] a = new int[n];
        int[] b = new int[n];
        int sa = 0, sb = 0;
        for (int i = 0; i < n; i++) {
            a[i] = sc.nextInt();
            b[i] = sc.nextInt();
            sa += a[i];
            sb += b[i];
        }
        for (int i = 0; i < n; i++) {
            if (sb - sa <= b[i] - a[i]) {
                System.out.println(i+1);
                return;
            }
        }
        System.out.println("impossible");
    }
}
