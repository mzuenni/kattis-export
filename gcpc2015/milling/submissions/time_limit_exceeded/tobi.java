import java.util.*;
import java.io.*;

public class tobi {
	public static void main(String args[]) {
		Scanner sc = new Scanner(System.in);
		int W = sc.nextInt();
		int S = sc.nextInt();
		int X = sc.nextInt();
		int Y = sc.nextInt();

		int Ws[][] = new int[W][X];
		for (int i = 0; i < W; i++) {
			for (int j = 0; j < X; j++) {
				Ws[i][j] = sc.nextInt();
			}
		}

		int Ss[][] = new int[S][X];
		for (int i = 0; i < S; i++) {
			for (int j = 0; j < X; j++) {
				Ss[i][j] = sc.nextInt();
			}
		}

		for (int i = 0; i < W; i++) {
			for (int j = 0; j < X; j++) {
				for (int k = 0; k < S; k++) {
					Ws[i][j] = Math.min(Ws[i][j], Y-Ss[k][j]);
				}
				if (j != 0) {
					System.out.print(" ");
				}
				System.out.print(Ws[i][j]);
			}
			System.out.println("");
		}
	}
}
