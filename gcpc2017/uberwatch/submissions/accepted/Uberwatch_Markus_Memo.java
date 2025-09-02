import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.Arrays;

public class Uberwatch_Markus_Memo {
	int lastSecond;
	int duration;
	int[] numberOpp;
	int[] memo;
	
	public Uberwatch_Markus_Memo(int lastSecond, int duration, int[] numberOpp) {
		this.lastSecond = lastSecond;
		this.duration = duration;
		this.numberOpp = numberOpp;
		this.memo = new int[numberOpp.length];
		Arrays.fill(memo, -1);
	}
	
	// fromSecond: from here, it takes m seconds until fully charged
	public int max(int fromSecond) {
		if (fromSecond+duration > lastSecond)
			return 0;
		if (memo[fromSecond] != -1)
			return memo[fromSecond];
		int max = -1;
		for (int i = fromSecond+duration; i <= fromSecond+duration+duration; i++) {
			if (i > lastSecond)
				break;
			int rec = numberOpp[i]+max(i);
//			System.out.println("num = "+numberOpp[i]+"Aufruf "+(i+1)+": "+max(i+1));
			if (rec > max)
				max = rec;
		}
		memo[fromSecond] = max;
		return max;
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
			int m = Integer.parseInt(split[1]);
			line = br.readLine();
			split = line.split(" ");
			int[] numberOpp = new int[n];
			for (int i = 0; i < n; i++) {
				numberOpp[i] = Integer.parseInt(split[i]);
			}
//			System.out.println(Arrays.toString(numberOpp));
			Uberwatch_Markus_Memo ub = new Uberwatch_Markus_Memo(n-1, m, numberOpp);
			System.out.println(ub.max(0));
			
			bw.close();
		}
		catch (IOException e) {
			e.printStackTrace();
		}
	}
}
