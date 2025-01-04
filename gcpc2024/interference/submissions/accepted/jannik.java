import java.util.*;
public class jannik {
  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    int n = in.nextInt();
    in.nextLong();
    long[] wp = new long[n], wl = new long[n], wa = new long[n];
    int k = 0;
  	while (n-- > 0) {
  		String c = in.next();
  		long p = in.nextLong();
  		if (c.equals("!")) {
  		  wp[k] = p;
  		  wl[k] = in.nextLong();
  		  wa[k++] = in.nextLong();
  		} else {
  			long sum = 0;
  			for (int i = 0; i < k; i++) {
  			  if (wp[i] > p || wp[i] + wl[i] <= p || (p - wp[i]) % 2 == 1)
  			    continue;
  			  sum -= (((p - wp[i]) % 4) - 1) * wa[i];
  			}
  			System.out.println(sum);
  		}
  	}
  }
}
