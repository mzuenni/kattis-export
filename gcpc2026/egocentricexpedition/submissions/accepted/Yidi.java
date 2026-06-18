import java.util.Scanner;

public class Yidi {
	public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int T = sc.nextInt();
        for (int t=0; t<T; t++) {
            System.out.println("? 0 1");
            System.out.flush();
            double d1 = sc.nextDouble();

            System.out.println("? 1 1");
            System.out.flush();
            double d2 = sc.nextDouble() * Math.sqrt(0.5);

            double d = Math.abs(d1*d2 / Math.sqrt(d2*d2 + (d1-d2)*(d1-d2)));
            System.out.print("! ");
            System.out.println(Math.round(d*d*4));
            System.out.flush();
        }
	}
}
