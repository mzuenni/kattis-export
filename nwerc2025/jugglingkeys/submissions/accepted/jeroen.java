import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;

public class jeroen {
	static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

	public static void main(String[] args) throws Exception {
		// Read input
		String[] ps = in.readLine().split(" ");
		int n = Integer.valueOf(ps[0]);
		int k = Integer.valueOf(ps[1]);
		int q = Integer.valueOf(ps[2]);

		int[] l = new int[q];
		int[] r = new int[q];
		for(int i = 0; i < q; i++) {
			ps = in.readLine().split(" ");
			l[i] = Integer.valueOf(ps[1]);
			r[i] = Integer.valueOf(ps[2]);
		}

		// Sort events by time
		Event[] events = new Event[q*2];
		for(int i = 0; i < q; i++) {
			events[i*2] = new Event(l[i], i, true);
			events[i*2+1] = new Event(r[i], i, false);
		}
		Arrays.sort(events);

		// Simulate and store which schedules need a key
		boolean[] needs = new boolean[q];
		int current = n;
		for(int i = 0; i < events.length; i++) {
			if(events[i].start) {
				current--;
			} else {
				if(current == 0) {
					needs[events[i].idx] = true;
				}
				current++;
			}
		}

		// Check if we have enough keys for the above schedule
		int keys = k;
		for(int i = events.length - 1; i >= 0; i--) {
			if(needs[events[i].idx]) {
				if(events[i].start) {
					keys++;
				} else {
					if(keys == 0) {
						System.out.println("IMPOSSIBLE");
						return;
					}
					keys--;
				}
			}	
		}

		// And print the schedule
		for(int i = 0; i < q; i++) {
			System.out.print(needs[i] ? "1" : "0");
		}
		System.out.println();
	}

	static class Event implements Comparable<Event> {
		public int time, idx;
		public boolean start;

		public Event(int time, int idx, boolean start) {
			this.time = time;
			this.idx = idx;
			this.start = start;
		}

		public int compareTo(Event other) {
			return this.time - other.time;
		}
	}
}
