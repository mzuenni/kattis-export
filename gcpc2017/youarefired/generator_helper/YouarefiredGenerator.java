import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Random;
import java.util.Scanner;
import java.util.Set;
import java.util.SplittableRandom;
import java.util.TreeSet;

public class YouarefiredGenerator 
{
	static SplittableRandom randEngine;
	
	public static int roll(int min, int max) 
	{
		return randEngine.nextInt(min, max+1);
	}
	
	public static long roll(long min, long max)
	{
		return randEngine.nextLong(min, max+1);
	}
	
	public static String getRandomName(int len)
	{
		String chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
		StringBuilder strbuild = new StringBuilder();
		for (int i = 0; i < len; ++i)
			strbuild.append(chars.charAt(roll(0, chars.length()-1)));
		return strbuild.toString();
	}
	
	public static List<String> generateNames(int n, int minNameLen, int maxNameLen)
	{
		Set<String> names = new TreeSet<String>();
		while (names.size() < n)
		{
			int nameLen = roll(minNameLen, maxNameLen);
			names.add(getRandomName(nameLen));
		}
		return new ArrayList<String>(names);
	}

	public static List<Long> generateSalary(int n, long minSal, long maxSal)
	{
		List<Long> salary = new ArrayList<Long>(n);
		for (int i = 0; i < n; ++i)
			salary.add(roll(minSal, maxSal));
		return salary;
	}
	
	public static long sumArray(List<Long> array, int from, int to)
	{
		long res = 0;
		for (int i = from; i < from+to; ++i)
			res += array.get(i);
		return res;
	}
	
	public static long sumArray(List<Long> array)
	{
		return sumArray(array, 0, array.size());
	}
	
	
	public static void output(int n, long d, int k, List<String> names, List<Long> salary)
	{
		System.out.println(n + " " + d + " " + k);
		for (int i = 0; i < n; ++i)
			System.out.println(names.get(i) + " " + salary.get(i));
	}
	
	
	public static void main(String[] args) 
    {
    	Scanner sc = new Scanner(System.in);
		randEngine = new SplittableRandom(sc.nextLong());
		int type = sc.nextInt();
		int minN = sc.nextInt();
		int maxN = sc.nextInt();
		long minSal = sc.nextLong();
		long maxSal = sc.nextLong();
		int minNameLen = sc.nextInt();
		int maxNameLen = sc.nextInt();
		
		int n = roll(minN, maxN);
		List<String> names = generateNames(n, minNameLen, maxNameLen);
		List<Long> salary = generateSalary(n, minSal, maxSal);
		Collections.sort(salary);
		Collections.reverse(salary);

		int k;
		long d;
		
		// possible
		if (type == 0)
		{
			k = roll(1,n);
			long maxD = sumArray(salary, 0, k);
			long minD = maxD/2;
			d = roll(Math.max(1, minD), maxD);
		}
		// impossible due to k
		else if (type == 1)
		{
			k = roll(1, n-1);
			long minD = sumArray(salary, 0, k) + 1;
			long maxD = sumArray(salary);
			d = roll(minD, maxD);
		}
		// impossible because totalSalary < d
		else
		{
			k = roll(1,n);
			d = sumArray(salary) + 1;	
		}
		Collections.shuffle(salary, new Random(randEngine.nextLong()));
		output(n, d, k, names, salary);
		sc.close();
    }
}
