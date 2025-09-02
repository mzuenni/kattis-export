import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Scanner;

public class ContestChaosEmi {

    static class Interval implements Comparable<Interval> {
        int start;
        int end;
        int weight;

        @Override
        public int compareTo(Interval o) {
            return end - o.end;
        }

        @Override
        public String toString() {
            return "[" + start + "-" + end + "](" + weight + ")";
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        List<Interval> list = new ArrayList<>();

        for (int i = 0; i < n; i++) {
            Interval in = new Interval();
            in.start = sc.nextInt();
            in.end = sc.nextInt();
            in.weight = sc.nextInt();
            sc.next();
            list.add(in);
        }

        Collections.sort(list);
        int[] dp = new int[n + 1];
        for (int i = 1; i <= n; i++) {
            int p = i;
            while (p > 0 && list.get(p - 1).end >= list.get(i - 1).start) {
                p--;
            }
            dp[i] = Math.max(dp[i - 1], list.get(i - 1).weight + dp[p]);
        }

        System.out.println(dp[n]);
        sc.close();
    }
}
