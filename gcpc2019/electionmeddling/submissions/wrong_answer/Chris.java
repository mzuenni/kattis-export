import java.util.*;

public class Chris {

    public static void main(String[] args) {

        var sc = new Scanner(System.in);

        var w = sc.nextInt();
        var p = sc.nextInt();

        PriorityQueue<Integer> bribes = new PriorityQueue<>();
        for (int i = 0; i < w; i++) {
            var own = sc.nextInt();
            var b = 0;
            var othermax = 0;
            for (int j = 0; j < p - 1; j++) {
                var v = sc.nextInt();
                if (own <= v) {
                    var mid = (int) Math.ceil((v - own) / 2.0);
                    own += mid;
                    v -= mid;
                    b += mid;
                    othermax = Math.max(othermax, v);
                }
            }
            if (own == othermax) {
                b++;
            }
            bribes.add(b);
        }
        var winwards = Math.floor(w / 2.0) + 1;
        var sum = 0;
        for (int i = 0; i < winwards; i++) {
            sum += bribes.poll();
        }
        System.out.println(sum);
    }

}
