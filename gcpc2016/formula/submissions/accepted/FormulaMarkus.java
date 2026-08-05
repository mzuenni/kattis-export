import java.util.Scanner;

public class FormulaMarkus {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		String line;
		String[] split;
		
		line = sc.nextLine();
		split = line.split(" ");
		double x0 = Double.parseDouble(split[0]);
		double y0 = Double.parseDouble(split[1]);
		line = sc.nextLine();
		split = line.split(" ");
		double x1 = Double.parseDouble(split[0]);
		double y1 = Double.parseDouble(split[1]);
		line = sc.nextLine();
		split = line.split(" ");
		double x2 = Double.parseDouble(split[0]);
		double y2 = Double.parseDouble(split[1]);
		line = sc.nextLine();
		sc.close();
		double measure = Double.parseDouble(line);
		
		double aSq = (x1-x0)*(x1-x0)+(y1-y0)*(y1-y0);
		double bSq = (x2-x0)*(x2-x0)+(y2-y0)*(y2-y0);
		double cSq = (x2-x1)*(x2-x1)+(y2-y1)*(y2-y1);
		// Let x = c1+c2 such that the c-height of the triangle separates c into c1, c2
		// Use the Pythagorean theorem twice to calculate c2.
		double c2Sq = ((cSq+bSq-aSq)*(cSq+bSq-aSq))/(cSq*4.0);
		double x = 	Math.sqrt(bSq-c2Sq);// height
		double r = (Math.sqrt(cSq)*x)/(Math.sqrt(aSq)+Math.sqrt(bSq)+Math.sqrt(cSq));
		// This does not write trailing zeroes...
		double trunc = (r/measure-1.0)*100000;
		if (trunc < 0) trunc -= 0.5; else trunc += 0.5;
		int tr = (int)trunc;
		System.out.println(tr/(double)1000.0);
	}
}
