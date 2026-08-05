import java.io.BufferedReader;
import java.io.InputStreamReader;

/*
 * a wrong way to put the clock upside down, more like mirroring it
 * 
 */

public class UpsideDownEgorWrongUpside {
	
	public static void main(String[] args) throws Exception{
        new UpsideDownEgorWrongUpside().run();
    }

	
	private void run() throws Exception{
		  BufferedReader reader=new BufferedReader(new InputStreamReader(System.in));
		  String prime=reader.readLine();
		  
		  if(!isPrime(Long.parseLong(prime))){
			  System.out.println("no");
			  return;
		  }
		  
		  Long upsideDown=Long.parseLong(makeUpsideDown(prime));
		  
		  if(isPrime(upsideDown))
			  System.out.println("yes");
		  else
			  System.out.println("no");
		  
	}
	
//	boolean isPrime(long z){
//		if(z==1L)
//			return false;
//		if(z%2==0)
//			return false;
//		long max=Math.min(z-1, 100_000_000L);
//		for(long i=3;i<max;i+=2)
//			if(z%i==0)
//				return false;
//			
//		return true;
//	}

boolean smallIsPrime(long z){
		if(z==1L)
			return false;
		for(long i=2L;i<z-1L;i++)
			if(z%i==0L)
				return false;
		
		return true;
	}
	
	boolean isPrime(long z){
		//System.out.println("number: "+z);
		if(z<1000L)
			return smallIsPrime(z);
		long end=(long)Math.ceil(Math.sqrt(z))+100L;
		
		//unroll_2:
		if(z%2L==0L)
			return false;
		//unroll_3
		if(z%3L==0L)
			return false;

		//unroll_5
		if(z%5L==0L)
			return false;		
		
		long[] kk={4L,2L,4L,2L,4L,6L,2L,6L};
		
		for(long i=7L;i<=end;){
			for(long d:kk){
				if(z%i==0L)
					return false;
				i+=d;
			}
		}
		
		return true;
	}
	
	
	String makeUpsideDown(String prime){
		String res="";
		for(int i=0;i<prime.length();i++){
			char ch=prime.charAt(i);
			switch(ch){
				case '0': res=res+'0'; break;//<-- here it should be '0'+res
				case '1': res=res+'1'; break;
				case '2': res=res+'2'; break;
				case '3': return "1";
				case '4': return "1";
				case '5': res=res+'5'; break;
				case '6': res=res+'9'; break;
				case '7': return "1";
				case '8': res=res+'8'; break;
				case '9': res=res+'6'; break;
				default:
					return "1";
			}		
		}
		return res;
	}
}

