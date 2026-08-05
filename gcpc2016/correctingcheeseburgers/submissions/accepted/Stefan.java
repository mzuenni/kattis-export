import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;

public class Stefan {
  public static void main(String[] args) {
    //read input
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    long t=0;
    long start = 0, end = 0;
    for(int i = 0; i < n; i++) {
      t = s.nextInt();
      start = start * n + (t-1);
      end = end * n + i;
    }
    Set<Long> reachable_start = new HashSet<Long>();
    reachable_start.add(start);                
    Set<Long> reachable_end = new HashSet<Long>();
    reachable_end.add(end);               

    //compute reachable nodes
    t = 0;
    while(!intersects(reachable_start, reachable_end)) {
      if(t % 2 == 0) {
        reachable_start = step(n, reachable_start, true);
      }
      else {
        reachable_end = step(n, reachable_end, false);
      }
      t++;
    }

    System.out.println(t);
  }
  
  public static boolean intersects(Set<Long> a, Set<Long> b) {
    for(Long t: a) {
      if(b.contains(t)) {
        return true;
      }
    }
    return false;
  }
  
  public static Set<Long> step(int n, Set<Long> reachable, boolean forward) {
    long[] pow = new long[n+1];
    pow[0] = 1;
    for(int i = 1; i <= n; i++) {
      pow[i] = n * pow[i-1];
    }
    
    Set<Long> ret = new HashSet<Long>();
    long pa, pb, pc, pd, p;
    for(long tt: reachable) {
      for(int b = 0; b <= n; b++) {
        for(int c = b; c <= n; c++) {
          for(int d = c; d <= n; d++) {
            long t = tt;
            pd = t % pow[n-d];
            t /= pow[n-d];
            pc = t % pow[d-c];
            t /= pow[d-c];
            pb = t % pow[c-b];
            t /= pow[c-b];
            pa = t % pow[b];
            p = forward ? pa * pow[n-d + c-b] + pb + pc * pow[b + n-d + c-b] + pd * pow[c-b] : pa * pow[d-c] + pb * pow[n-d + b + d-c] + pc + pd * pow[d-c + b];
            if(!ret.contains(p)) {
              ret.add(p);
            }
          }
        }
      }                                                                                                                                                
    }
    
    return ret;
  }
}
