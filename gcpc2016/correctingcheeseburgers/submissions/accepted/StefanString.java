import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;

public class StefanString {
  public static void main(String[] args) {
    //read input
    Scanner s = new Scanner(System.in);
    int n = s.nextInt(), t;
    String start = "", end = "";
    for(int i = 0; i < n; i++) {
      t = s.nextInt();
      start += t-1;
      end += i;
    }
    Set<String> reachable_start = new HashSet<String>();
    reachable_start.add(start);                
    Set<String> reachable_end = new HashSet<String>();
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
  
  public static boolean intersects(Set<String> a, Set<String> b) {
    for(String t: a) {
      if(b.contains(t)) {
        return true;
      }
    }
    return false;
  }
  
  public static Set<String> step(int n, Set<String> reachable, boolean forward) {
    Set<String> ret = new HashSet<String>();
    for(String t: reachable) {
      for(int b = 0; b <= n; b++) {
        for(int c = b; c <= n; c++) {
          for(int d = c; d <= n; d++) {
            String pa = t.substring(0, b);
            String pb = t.substring(b, c);
            String pc = t.substring(c, d);
            String pd = t.substring(d);
            String p = forward ? pc + pa + pd + pb : pb + pd + pa + pc;
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
