import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Scanner;
import java.util.Locale;

public class FormulaMoritz {

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		String in = br.readLine();
		String[] split = in.split(" ");
		double a_x = Double.parseDouble(split[0]);
		double a_y = Double.parseDouble(split[1]);
		
		in = br.readLine();
		split = in.split(" ");
		double b_x = Double.parseDouble(split[0]);
		double b_y = Double.parseDouble(split[1]);
		
		in = br.readLine();
		split = in.split(" ");
		double c_x = Double.parseDouble(split[0]);
		double c_y = Double.parseDouble(split[1]);
		
		in = br.readLine();
		double given_r = Double.parseDouble(in);
		
		double a = Math.sqrt((a_x - b_x)*(a_x - b_x) + (a_y - b_y)*(a_y - b_y));
		double b = Math.sqrt((a_x - c_x)*(a_x - c_x) + (a_y - c_y)*(a_y - c_y));
		double c = Math.sqrt((c_x - b_x)*(c_x - b_x) + (c_y - b_y)*(c_y - b_y));
		
		double r = (a+b+c)/2;
		double area = Math.sqrt(r*(r-a)*(r-b)*(r-c));
		
		double formula_r = 2* area / (a+b+c);
		
		Locale.setDefault(new Locale("en", "US"));
		System.out.printf("%.3f\n" , 100*formula_r/given_r-100);

	}

}
