import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;

public class jeroen {
	static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

	public static void main(String[] args) throws Exception {
		String s = in.readLine();
		if(s.equals("send"))
			send();
		else if(s.equals("receive"))
			receive();
		else
			throw new Exception();
	}

	public static void send() throws Exception {
		int n = Integer.valueOf(in.readLine());
		String s = in.readLine();
		for (int i = 0; i < 5; i++) {
			for(int b = 2; b >= 0; b--)
				System.out.print((i & (1 << b)) != 0 ? '1' : '0');
			for (int j = 0; j < n; j++) {
				int x = s.charAt(j) - 'a';
				System.out.print((x & (1 << i)) != 0 ? '1' : '0');
			}
			System.out.println();
		}
	}

	public static void receive() throws Exception {
		String[] lines = new String[5];
		for (int i = 0; i < 5; i++)
			lines[i] = in.readLine();
		Arrays.sort(lines);
		int n = lines[0].length() - 3;
		for (int i = 0; i < n; i++) {
			int x = 0;
			for (int b = 0; b < 5; b++)
				if (lines[b].charAt(3 + i) == '1')
					x |= 1 << b;
			System.out.print((char) (x + 'a'));
		}
		System.out.println();
	}
}
