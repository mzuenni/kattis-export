import java.util.Scanner;

class YvonneAccepted {
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);

		int t = scanner.nextInt();

		if (t <= 6 * 60)
			System.out.println(0);
		else if (t <= 6 * 60 + 30)
			System.out.println(t - 6 * 60);
		else if (t <= 9 * 60 + 30)
			System.out.println(30);
		else if (t <= 9 * 60 + 45)
			System.out.println(t - 9 * 60);
		else if (t <= 10 * 60 + 45)
			System.out.println(45);
		else
			System.out.println(t - 10 * 60);
	}
}
