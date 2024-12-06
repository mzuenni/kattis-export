import java.util.Scanner;

public class MaartenScanner {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        long k = scanner.nextLong();
        String s = scanner.next();

        long offset = 1, base = 2;
        while (k > 0) {
            if ((k & 1) == 1) {
                offset = (offset * base) % n;
            }
            k >>= 1;
            base = (base * base) % n;
        }

        StringBuilder result = new StringBuilder();
        for (int i = 0; i < n; ++i) {
            result.append(s.charAt((int) ((i * offset) % n)));
        }

        System.out.println(result.toString());
        scanner.close();
    }
}
