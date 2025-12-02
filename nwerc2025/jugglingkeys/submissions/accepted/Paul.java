import java.util.*;

public class Paul {
    public static class Event implements Comparable<Event> {
        int t, i;
        public Event(int t, int i) {
            this.t = t;
            this.i = i;
        }

        public int compareTo(Event e) {
            if (t != e.t) return t - e.t;
            return i - e.i;
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int k = sc.nextInt();
        int q = sc.nextInt();
        Event[] events = new Event[2*q];
        for (int i = 0; i < q; i++) {
            sc.next();
            int l = sc.nextInt();
            int r = sc.nextInt();
            events[2*i] = new Event(l, i);
            events[2*i+1] = new Event(r, ~i);
        }
        Arrays.sort(events);

        int depth = 0;
        boolean[] needKey = new boolean[q];
        for (Event e: events) {
            if (depth == n) needKey[~e.i] = true;
            depth += e.i >= 0 ? 1 : -1;
        }

        for (Event e: events) {
            if (e.i >= 0 && needKey[e.i]) k--;
            if (e.i < 0 && needKey[~e.i]) k++;
            if (k < 0) {
                System.out.println("impossible");
                return;
            }
        }

        for (boolean b: needKey) {
            System.out.print(b ? '1' : '0');
        }
        System.out.println();
    }
}
