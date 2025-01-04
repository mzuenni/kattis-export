import java.io.*;
public class jannik_fast {
  public static void main(String[] args) throws IOException {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    String[] line = br.readLine().split(" ");
    int n = Integer.parseInt(line[0]);
    long h = Long.parseLong(line[1]), res = 0;
    boolean ok = true;
    for (int i = 0; i < n; i++) {
      line = br.readLine().split(" ");
      long x = Long.parseLong(line[0]), y = Long.parseLong(line[1]), z = Long.parseLong(line[2]);
      long tmp = (long) 1.1e9;
      if (Math.min(x,y) <= h)
        tmp = z;
      if (y < tmp && Math.min(x,z) <= h)
        tmp = y;
      if (x < tmp && Math.min(y,z) <= h)
        tmp = x;
      if (tmp > 1e9)
        ok = false;
      res += tmp;
    }
    System.out.println(ok ? res : "impossible");
  }
}
