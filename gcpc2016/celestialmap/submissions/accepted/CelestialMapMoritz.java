import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class CelestialMapMoritz {

	public static void main(String[] args) throws IOException {
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		//BufferedReader br = new BufferedReader(new FileReader("data.in"));
		
		double eps = 10e-7;
		String in;
		
		//in = br.readLine();
		//int t = Integer.parseInt(in);
		int t = 1;
		
		for(int tc=1;tc<=t;tc++) {
			
			in = br.readLine();
			String[] split = in.split(" ");
			int n = Integer.parseInt(split[0]);
			double dist = Double.parseDouble(split[1]);
			
			double[][] plane = new double[2][3];
			in = br.readLine();
			split = in.split(" ");
			plane[0][0] = Double.parseDouble(split[0]);
			plane[0][1] = Double.parseDouble(split[1]);
			plane[0][2] = Double.parseDouble(split[2]);
			in = br.readLine();
			split = in.split(" ");
			plane[1][0] = Double.parseDouble(split[0]);
			plane[1][1] = Double.parseDouble(split[1]);
			plane[1][2] = Double.parseDouble(split[2]);
			
			MyPlane p = new MyPlane(plane[0],plane[1]);
			
			double[][] stars = new double[n][3];
			double[][] trajectories = new double[n][3];
			double[] speed = new double[n];
			
			for(int i=0;i<n;i++) {
				in = br.readLine();
				split = in.split(" ");
				stars[i][0] = Double.parseDouble(split[0]);
				stars[i][1] = Double.parseDouble(split[1]);
				stars[i][2] = Double.parseDouble(split[2]);
				
				in = br.readLine();
				split = in.split(" ");
				trajectories[i][0] = Double.parseDouble(split[0]);
				trajectories[i][1] = Double.parseDouble(split[1]);
				trajectories[i][2] = Double.parseDouble(split[2]);
				
				speed[i] = norm(trajectories[i]);
			}
			
			int starsFound = 0;
			
			for(int i=0;i<n;i++) {
				double[] intersection = p.intersection(stars[i], trajectories[i]);
				double d = norm(intersection);
				double d2 = distance(stars[i],intersection);
				
				double[] test = new double[3];
				test[0] = stars[i][0] - d*trajectories[i][0];
				test[1] = stars[i][1] - d*trajectories[i][1];
				test[2] = stars[i][2] - d*trajectories[i][2];
				
				double valid = distance(intersection, test);
				
				//System.out.println(valid);
				
				if(valid <= eps && Math.abs(d-dist) <= eps &&  Math.abs(d-d2/speed[i]) <= eps) {
					starsFound++;
				}
			}
			
			System.out.println(starsFound);
			
			if(tc != t)
				br.readLine();
		}
	}
	
	public static double norm(double[] star) {
		return Math.sqrt(star[0]*star[0] + star[1]*star[1] + star[2]*star[2]);
	}
	
	public static double distance(double[] a, double[] b) {
		return Math.sqrt((a[0]-b[0])*(a[0]-b[0]) + (a[1]-b[1])*(a[1]-b[1]) + (a[2]-b[2])*(a[2]-b[2]));
	}
	
	static class MyPlane {
		
		double[] normal = new double[3]; 
		double eps = 10e-6;
		
		public MyPlane(double[] v1, double[] v2) {
			normal[0] = v1[1]*v2[2] - v1[2]*v2[1];
			normal[1] = v1[2]*v2[0] - v1[0]*v2[2];
			normal[2] = v1[0]*v2[1] - v1[1]*v2[0];
			
			double norm = norm(normal);
			normal[0] /= norm;
			normal[1] /= norm;
			normal[2] /= norm;
		}
		
		public double[] intersection(double[] offset, double[] v3) {
			double[] ret = new double[3];
			
			double c = - (normal[0] * offset[0] + normal[1] * offset[1] + normal[2] * offset[2])/(normal[0]*v3[0] + normal[1] * v3[1] + normal[2] * v3[2]); 
						
			ret[0] = offset[0] + c*v3[0];
			ret[1] = offset[1] + c*v3[1];
			ret[2] = offset[2] + c*v3[2];
			
			return ret;
		}
		
		public double[] projection(double[] v3) {
			if(isInPlane(v3)) return v3;
			else return intersection(v3,normal);
		}
		
		public boolean isParallel(double[] v3) {
			double res = (normal[0] * (v3[0])) +(normal[1] * (v3[1])) + (normal[2] * (v3[2]));
			
			if (Math.abs(res) <= eps) {
				return true;
			}
			return false;
		}
		
		public boolean isInPlane(double[] v3) {
			double res = (normal[0] * v3[0]) +(normal[1] * v3[1]) + (normal[2] * v3[2]);
			
			if(Math.abs(res) <= eps) {
				return true;
			}
			return false;
		}
	}
	
}
