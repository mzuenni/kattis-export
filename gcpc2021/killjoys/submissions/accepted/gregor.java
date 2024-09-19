import java.math.BigInteger;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;

public class gregor {

    public static List<Integer>[] adj = new List[1000000];
    public static int[] bip;

    public static boolean bipDFS(int i, int side) {
        if (bip[i] != -1) {
            if (bip[i] == side) return true;
            else return false; // not bipartite
        }

        bip[i] = side;

        for (int n : adj[i])
            if (!bipDFS(n, 1 - side))
                return false;

        return true;
    }


    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int m = sc.nextInt();
        int p = sc.nextInt();

        for (int i = 0; i < n; i++)
            adj[i] = new LinkedList<>();

        for (int i = 0; i < m; i++) {
            int a = sc.nextInt() - 1;
            int b = sc.nextInt() - 1;

            adj[a].add(b);
            adj[b].add(a);
        }

        bip = new int[n];
        for (int i = 0; i < n; i++) bip[i] = -1;
        int bipC = 0;
        boolean hasBip = true;
        for (int i = 0; i < n; i++)
            if (bip[i] == -1) {
                bipC++;
                hasBip &= bipDFS(i, 0);
            }

        if (!hasBip)
            System.out.println("impossible");
        else
            System.out.println(BigInteger.valueOf(2).pow(bipC - 1).add(BigInteger.ONE).mod(BigInteger.valueOf(p)));
    }
}
