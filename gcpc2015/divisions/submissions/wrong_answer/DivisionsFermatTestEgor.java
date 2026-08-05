import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.math.BigInteger;

/*

This solution uses a very rudimentary primality test (Fermat test with basis 2), so I would expect it to fail.

However, Fermat test doesn't seem to be such a stupid idea: Carmichael numbers are products
of at least 3 primes. In our case we know there are at most two factors, so the possibility of
Carmichael numbers is ruled out.

A solution using more than just one base would not be easy to prove wrong.

*/
public class DivisionsFermatTestEgor {
	public static void main(String[] args)throws Exception{
        new DivisionsFermatTestEgor().run();
    }
	
	private void run() throws Exception{
		  BufferedReader reader=new BufferedReader(new InputStreamReader(System.in));
		  long N=Long.parseLong(reader.readLine());
		  System.out.println(getDivisorCnt(N));	  
		  reader.close();
	}
	
    boolean isQuadrat(long N){
    	double d=Math.sqrt(N);
    	
    	long start=(long)Math.ceil(d-10);
    	long end=(long)Math.ceil(d+10);
    	for(long i=start;i<=end;i++)
    		if(i*i==N)
    			return true;
    	return false;
    }
	
	long getDivisorCnt(long N){
		long res=1;
		for(long i=2;i<=1_000_000;++i){
			long cnt=1;
			while(N%i==0){
				N/=i;
				cnt++;
			}
			res*=cnt;
		}
		
		if(N==1)
			return res;
		
		//there is still something there, but we know: this one is prime or has two factors
		if(isPrim(N))
			return res*2L;
		else{//is not prime, but we know there are at most two factors
			if(isQuadrat(N))//the factors are the same:
				return res*3L;
			else//factors are different
				return res*4L;
		}
	}
	
	
	boolean isPrim(long N){
		long[] bases={2};
		for(long base:bases)
			if(power(base, N-1, N)!=1)
				return false;
		return true;
	}
	
	long power(long basis, long pow, long M){
		long res=1;
		long current=2;
		while(pow!=0){
			if((pow&1)!=0)
				res=multMod(res, current, M);
			current=multMod(current, current, M);
			pow/=2;
		}
		return res;
	}
	
	long multMod(long a, long b, long M){
		return BigInteger.valueOf(a).multiply(BigInteger.valueOf(b)).mod(BigInteger.valueOf(M)).longValue();
	}
}
