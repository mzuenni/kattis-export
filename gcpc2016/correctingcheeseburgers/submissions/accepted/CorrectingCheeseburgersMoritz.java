import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;

public class CorrectingCheeseburgersMoritz {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		String in = "";
		for(int i=0;i<n;i++) {
			in += (sc.nextInt()-1);
		}
		
		String out = ("0123456789").substring(0,n);
		
		Set<String> bfs = new HashSet<String>();
		bfs.add(in);
		Set<String> bfs_backward = new HashSet<String>();
		bfs_backward.add(out);
		
		int steps = 0;
		
		while(!connected(bfs,bfs_backward)) {
			if(steps%2==0) {
				Set<String> new_bfs = shuffle(bfs,false);
				bfs = new_bfs;
			} else {
				Set<String> new_bfs_backward = shuffle(bfs_backward,true);
				bfs_backward = new_bfs_backward;
			}
			steps++;
		}
		
		System.out.println(steps);
	}

	public static boolean connected(Set<String> bfs, Set<String> bfs_backwards) {
		for(String s:bfs) {
			if(bfs_backwards.contains(s)) {
				return true;
			}
		}
		return false;
	}
	
	public static Set<String> shuffle(Set<String> states,boolean reverse) {
		Set<String> new_states = new HashSet<String>();
		
		for(String state:states) {
			int n = state.length();
			for(int i=0;i<=n;i++) {
				for(int j=i;j<=n;j++) {
					for(int k=j;k<=n;k++) {
						String a = state.substring(0, i);
						String b = state.substring(i, j);
						String c = state.substring(j, k);
						String d = state.substring(k, n);
						
						String new_state;
						if(!reverse) {
							new_state = c+a+d+b;
						} else {
							new_state = b+d+a+c;
						}
						
						if(!new_states.contains(new_state)) {
							new_states.add(new_state);
						}
					}
				}
			}
		}
		
		return new_states;
	}
	
}
