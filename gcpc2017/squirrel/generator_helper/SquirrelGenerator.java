import java.util.ArrayList;
import java.util.Collections;
import java.util.Random;
import java.util.Scanner;

public class SquirrelGenerator {
    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        Random r = new Random(sc.nextLong());

        int minn = sc.nextInt();
        int maxn = sc.nextInt();

        int n = roll(r, minn, maxn);


        int rat = roll(r, 0, n - 1);
        int h = roll(r, 0, n - 1);
        while (h == rat) {
            h = roll(r, 0, n - 1);
        }
        int m = roll(r, 0, n - 1);
        while (m == rat || m == h) {
            m = roll(r, 0, n - 1);
        }
        
        // Generate tree
        ArrayList<String> edges = new ArrayList<>(n);
        ArrayList<Integer> nodes = new ArrayList<Integer>(), nodes_ = new ArrayList<Integer>();
        for(int j = 0; j < n; j++){
            nodes.add(j);
        }
        nodes_.add(r.nextInt(n));
        nodes.remove(nodes_.get(0));
        for(int j = 0; j < (n - 1); j++){
            int pre = r.nextInt(nodes_.size());
            int post = r.nextInt(nodes.size());
            int pre_val = nodes_.get(pre);
            int post_val = nodes.get(post);
            nodes_.add(post_val);
            nodes.remove(post);
            if (pre_val < post_val) {
                edges.add((pre_val + 1) + " " + (post_val + 1));
            } else {
                edges.add((post_val + 1) + " " + (pre_val + 1));
            }
        }
        Collections.shuffle(edges, r);
        
        System.out.println(n);
        System.out.println(rat);
        System.out.println(h);
        System.out.println(m);
        for (String e : edges) {
            System.out.println(e);
        }
    }

    public static int roll(Random r, int min, int max) {
        return min + r.nextInt(max - min + 1);
    }
}
