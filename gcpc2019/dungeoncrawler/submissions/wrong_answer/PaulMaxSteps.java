import java.util.*;

public class PaulMaxSteps {
	static final int STEPS = 250000;

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		for (int i = 0; i <= n; i++) sc.nextLine();
		
		for (int i = 0; i < STEPS; i++) {
			sc.next();
			System.out.println("W " + sc.next().charAt(0));
			System.out.flush();
		}
	}
}
