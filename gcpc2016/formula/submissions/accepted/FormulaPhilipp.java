import java.util.Locale;
import java.util.Scanner;

public class FormulaPhilipp {
	public static void main(String[] args) {
		Locale.setDefault(new Locale("en", "US"));
		
		Scanner sc = new Scanner(System.in);
		double[][] vert = new double[3][2];
		for (int i = 0; i < vert.length; i++) {
			for (int j = 0; j < vert[i].length; j++) {
				vert[i][j] = sc.nextInt();
			}
		}
		double r = sc.nextDouble();
		double[] sides = { dist(vert[0], vert[1]), dist(vert[1], vert[2]),
				dist(vert[0], vert[2]) };
		// s for herons formula
		double s = (sides[0]+sides[1]+sides[2])/2;
		double area = Math.sqrt(s*(s-sides[0])*(s-sides[1])*(s-sides[2]));
		double realR = area / s;
		System.out.println(100*(realR - r)/r);
		sc.close();
	}

	static double dist(double[] p1, double[] p2) {
		return Math.sqrt(Math.pow(p2[0] - p1[0], 2)
				+ Math.pow(p2[1] - p1[1], 2));
	}
}
