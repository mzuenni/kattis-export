import java.util.*;
public class wendy {
    static long k; 

    static long greedy(Long[] wash, Long[] doubles, int i, long abc) {
        wash[i] += doubles[0]; // put AB completely in A or in B (try both)
        for(int j = 0; j < 2; j++) {
            long r = (k - (wash[j] % k)) % k; 
            wash[j] += Math.min(r, doubles[2 - j]); // fill A (B) (to multiple of k) using AC (BC)
            wash[2] += doubles[2 - j] - Math.min(r, doubles[2 - j]); // put rest of AC (BC) into C 
            long add = Math.min((k - (wash[j] % k)) % k, abc); 
            wash[j] += add; 
            abc -= add; 
        }
        wash[2] += abc; 
        long res = 0; 
        for(int j = 0; j < 3; j++) {
            if (wash[j] % k == 0) res += wash[j] / k; 
            else res += wash[j] / k + 1; 
        }
        return res; 
  }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int t = in.nextInt();

        while (t > 0) {
            t--;
            long abc; 
            k = in.nextLong(); 
            Long[] wash = new Long[3]; 
            Long[] doubles = new Long[3]; 

            for (int i = 0; i < 3; i++) wash[i] = in.nextLong(); 
            for (int i = 0; i < 3; i++) doubles[i] = in.nextLong(); 

            abc = in.nextLong(); 

            long bestWash = (long) (9 * 1e9); 

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 2; j++) {
                    Long[] wash2 = wash.clone();
                    Long[] doubles2 = doubles.clone(); 
                    bestWash = Math.min(greedy(wash2, doubles2, j, abc), bestWash); 
                }
                Collections.rotate(Arrays.asList(wash), 1); 
                Collections.rotate(Arrays.asList(doubles), 1); 
            }
            System.out.println(bestWash);
        }
    }
}
