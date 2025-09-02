import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.Arrays;

public class youAreFired_Markus {

	public static class EmployeeSalary implements Comparable<EmployeeSalary> {
		String name;
		long salary;
		
		public EmployeeSalary(String name, long salary) {
			this.name = name;
			this.salary = salary;
		}

		// (not software engineering-proof)
		public int compareTo(EmployeeSalary o) {
			if (this.salary < o.salary)
				return 1;
			if (this.salary > o.salary)
				return -1;
			return 0;
		}
		
		public String toString() {
			return this.name+","+this.salary;
		}
		
		
	}
	
	public static void main(String[] args) {
		InputStreamReader is = new InputStreamReader(System.in);
		BufferedReader br = new BufferedReader(is);
		OutputStreamWriter os = new OutputStreamWriter(System.out);
		BufferedWriter bw = new BufferedWriter(os);
		
		try {
			
			String line;
			line = br.readLine();
			String[] split = line.split(" ");
			int n = Integer.parseInt(split[0]);
			long d = Long.parseLong(split[1]);
			int k = Integer.parseInt(split[2]);
			
//			System.out.println("n="+n+", d="+d+", k="+k);
			EmployeeSalary[] arr = new EmployeeSalary[n];
			for (int i = 0; i < n; i++) {
				line = br.readLine();
				split = line.split(" ");
				arr[i] = new EmployeeSalary(split[0], Long.parseLong(split[1]));
			}
			br.close();
			Arrays.sort(arr);
//			System.out.println(Arrays.toString(arr));
			
			String output = "";
			long sum = 0;
			int stop = -1;
			LOOP:
			for (int i = 0; i < k; i++) {
				sum += arr[i].salary;
				if (sum >= d) {
					stop = i;
					break LOOP;
				}
			}
			if (sum < d)
				bw.write("impossible\n");
			else {
				bw.write((stop+1)+"\n");
				for (int i = 0; i <= stop; i++) {
					bw.write(arr[i].name+", YOU ARE FIRED!\n");
				}
			}
			bw.close();
			
		}
		catch (IOException e) {
			e.printStackTrace();
		}
		
		
		
		
	}
}
