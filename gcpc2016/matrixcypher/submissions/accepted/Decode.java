import java.util.*;
import java.math.*;

class Decode {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
                BigInteger ka,kb,kc,kd;
                int n;
                BigInteger a,b,c,d;

                ka=new BigInteger("1");
                kb=new BigInteger("0");
                kc=new BigInteger("0");
                kd=new BigInteger("1");

                n=1;//sc.nextInt();
                for (int i=0;i<n;i++) {
                    a=new BigInteger(sc.next());
                    b=new BigInteger(sc.next());
                    c=new BigInteger(sc.next());
                    d=new BigInteger(sc.next());
                    String s="";
                    int bitcnt=0;
                    int x=0;
                    while (!a.equals(ka) || !b.equals(kb) || !c.equals(kc) || !d.equals(kd)) {
                        x=(x<<1);
                        bitcnt+=1;
                        if (a.compareTo(c)==1 || b.compareTo(d)==1) {
                            x+=1;
                            a=a.subtract(c);
                            b=b.subtract(d);
                        } else {
                            c=c.subtract(a);
                            d=d.subtract(b);
                        }
//                         if (bitcnt==8) {
                            s+=(char)(x+'0');
                            bitcnt=0;
                            x=0;
//                         }
                    }
                    System.out.println(s);
                }
	}
} 
