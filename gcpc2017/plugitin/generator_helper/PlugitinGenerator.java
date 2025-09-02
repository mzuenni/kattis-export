import java.util.ArrayList;
import java.util.Collections;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Random;
import java.util.Scanner;
import java.util.Set;
import java.util.Random;
import java.util.TreeSet;

public class PlugitinGenerator 
{
	
	static Random randEngine;
	
    public static int roll(int min, int max) {
        return min + randEngine.nextInt(max - min + 1);
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
	
	
	public static void main(String[] args) 
    {
    	Scanner sc = new Scanner(System.in);
		randEngine = new Random(sc.nextLong());
		
		int minN = sc.nextInt();
		int maxN = sc.nextInt();
		
		int minM = sc.nextInt();
		int maxM = sc.nextInt();
		
		int minConnections = sc.nextInt();
		int maxConnections = sc.nextInt();
		
		int N = roll(minN, maxN);
		int M = roll(minM, maxM);
		
		int totalConnections = 0;
		List<int[]> cons = new LinkedList<int[]>(); 
		
		for (int i=1; i<=M; i++) {
			List<Integer> possibleNeighbors = new LinkedList<Integer>();
			for(int j=1; j<=N; j++) possibleNeighbors.add(j);
			Collections.shuffle(possibleNeighbors, randEngine);
			
			int connections = roll(minConnections, maxConnections);
			for(int con=0; con<connections; con++) {
				cons.add(new int[]{i,possibleNeighbors.get(con)});
			}
			totalConnections += connections;
		}
		
		System.out.printf("%d %d %d\n", M,N, totalConnections);
		
		for(int[] con : cons) {
			System.out.printf("%d %d\n", con[0], con[1]);
		}
		
		sc.close();
    }
}
