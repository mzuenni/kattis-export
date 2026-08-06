import java.util.*;

// submission 6416547

public class godmar
{
    public static void main(String []av) {
        var s = new Scanner(System.in);
        int n = s.nextInt();
        for (int i = 0; i < n; i++) {
            long K = s.nextLong();
            long C = s.nextLong();
            // K * X + 1 = 0 (C)
            // -K * X = 1 (C)
            //
            if (K == C && K == 1)
                System.out.println(2);
            else if (gcd(K, C) != 1)
                System.out.println("IMPOSSIBLE");
            else {
                long X = modInvEuclid(-K, C);
                long Y = (K * X + 1) / C;
                System.out.println(Y);
            }
        }
    }

    /**
     * Finds a single solution {x, y} to the LDE a*x + b*y = c.
     * Outputs an array of the form {x, y, d}, where d = GCD(a,b).
     */
    private static long[] solveDiophantine(long a, long b, long c) {
      long[] e = compute(a, b);
      long k = c / e[2];

      //c not divisible by the GCD(a,b) -> no solution
      if (c - k*e[2] != 0)
        return null;

      long[] output = {e[0] * k, e[1] * k, e[2]};
      return output;
    }

    /**
     * Extended Euclidean Algorithm finds {x, y, d}
     * where d=GCD(a,b) and x and y satisfy a*x + b*y = d
     * The output is an array of the form {x, y, d}.
     */
    public static long[] compute (long a, long b) {
        long s0 = 1, s1 = 0, sTemp;
        long t0 = 0, t1 = 1, tTemp;
        long r0 = a, r1 = b, rTemp;
        long q;
        
        while (r1 != 0) {
            //q = r0 / r1;
            q = Math.floorDiv(r0, r1);
            
            rTemp = r1;
            r1 = r0 - q*r1;
            r0 = rTemp;
            
            sTemp = s1;
            s1 = s0 - q*s1;
            s0 = sTemp;
            
            tTemp = t1;
            t1 = t0 - q*t1;
            t0 = tTemp;
        }
        
        long[] output = {s0, t0, r0};
        return output;
    }

    public static long gcd(long a, long b) {
        long[] eea = compute(a, b);
        return eea[2];
    }

    /* Gets the modular inverse of a
     * This funciton does not depend on MOD being prime, but does require 
     * typing out the extended euclidean algorithm. 
     * That can be found at ~/book/wf_code/ExtendedEucliean.java
     * Complexity: log(a+ MOD) */
    static long modInvEuclid(long a, long MOD) {
        return (compute(a, MOD)[0] + MOD) % MOD;
    }
}

