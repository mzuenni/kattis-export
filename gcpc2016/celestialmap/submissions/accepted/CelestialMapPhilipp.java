
import java.util.Scanner;

public class CelestialMapPhilipp {
	static double eps = 0.001;
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		double d = sc.nextDouble();
		double[][] plane = new double[2][3];
		for (int i = 0; i < plane.length; i++) {
			for (int j = 0; j < plane[i].length; j++) {
				plane[i][j] = sc.nextDouble();
			}
		}
		double[] planeNormal = new double[3];
		planeNormal[0] = plane[0][1]*plane[1][2]-plane[0][2]*plane[1][1];
		planeNormal[1] = plane[0][2]*plane[1][0]-plane[0][0]*plane[1][2];
		planeNormal[2] = plane[0][0]*plane[1][1]-plane[0][1]*plane[1][0];
		double[][] position = new double[n][3];
		double[][] trajectory = new double[n][3];
		int count = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < position[i].length; j++) {
				position[i][j] = sc.nextDouble();
			}
			for (int j = 0; j < trajectory[i].length; j++) {
				trajectory[i][j] = sc.nextDouble();
			}
		}
		for (int i = 0; i < n; i++) {
			// the message took time d (in years), calculate where the star was back then
			for (int j = 0; j < position[i].length; j++) {
				position[i][j] -= d*trajectory[i][j];
			}
			// check whether this is reasonably close to the plane
			double dist = planeNormal[0]*position[i][0]+planeNormal[1]*position[i][1]+planeNormal[2]*position[i][2];
			if (dist > eps) {
				continue;
			}
			// check whether it is about distance d to Bob
			dist = Math.sqrt(Math.pow(position[i][0],2)+Math.pow(position[i][1], 2)+Math.pow(position[i][2], 2));
			if (Math.abs(dist-d)<eps) {
				count++;
			}
		}
		System.out.println(count);
	}
}
