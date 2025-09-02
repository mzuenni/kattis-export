import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.Scanner;

public class ContestChaosMoritz {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		List<Item> list = new ArrayList<Item>();
		for(int i=0;i<n;i++) {
			Item it = new Item();
			it.start = sc.nextInt();
			it.end = sc.nextInt();
			it.prize = sc.nextInt();
			sc.next();
			list.add(it);
		}
		
		Collections.sort(list,new Comparator<Item>(){
			public int compare(Item a, Item b) {
				return a.end-b.end;
			}
		});
		
		List<Item> looking = new ArrayList<Item>();
		//System.out.println(n);
		for(int i=n;i>0;i--) {
			int rounds = looking.size();
			List<Item> removeMe = new ArrayList<Item>();
			for(int j=0;j<rounds;j++) {
				Item it = looking.get(j);
				//System.out.println(j+" "+it);
				//System.out.println(it+" -?> " + list.get(i-1) + ": " + (it.start > list.get(i-1).end) + " "+i);
				if(it.start > list.get(i-1).end) {
					it.prev = i;
					removeMe.add(it);
				}
			}
			looking.removeAll(removeMe);
			looking.add(list.get(i-1));
			//System.out.println("Adding" + list.get(i-1));
		}
		
		/*
		for(int i=0;i<n;i++) {
			System.out.println((i+1)+" "+list.get(i).prev);
			if(list.get(i).prev >= 1)
				System.out.println(list.get(i)+" -> " + list.get(list.get(i).prev-1));
			else
				System.out.println(list.get(i).start+","+list.get(i).end + " -> Nothing");
		}
		*/
		
		int[] dp = new int[n+1];
		
		for(int i=1;i<=n;i++) {
			int p=list.get(i-1).prev;
			dp[i] = Math.max(dp[i-1], list.get(i-1).prize + dp[p]);
		}
		
		System.out.println(dp[n]+"\n");
	}
	
	public static class Item {
		int start = 0;
		int end = 0;
		int prize = 0;
		int prev = 0;
		
		public String toString() {
			return start+", "+end;
		}
	}

}
