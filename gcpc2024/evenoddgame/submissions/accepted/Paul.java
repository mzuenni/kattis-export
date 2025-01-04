import java.util.*;

public class Paul {
    boolean visited[][][][][];
    boolean dp[][][][][];
    boolean win(int who, int cur, int a, int b, int c) {
        if (a+b+c == 0) return who == cur;
        if (visited[who][cur][a][b][c]) return dp[who][cur][a][b][c];
        visited[who][cur][a][b][c] = true;

        dp[who][cur][a][b][c] =
            (a > 0 && !win(1-who, cur,   a-1, b, c)) ||
            (b > 0 && !win(1-who, 1-cur, a, b-1, c)) ||
            (c > 0 && !win(1-who, 0,     a, b, c-1));
        return dp[who][cur][a][b][c];
    }

    void run() {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();

        char op[] = new char[n];
        int val[] = new int[n];
        int type[] = new int[n];
        int count[] = new int[3];
        for (int i = 0; i < n; i++) {
            op[i] = sc.next().charAt(0);
            val[i] = sc.nextInt();
            if (op[i] == '+' && val[i]%2 == 1) type[i] = 1;
            if (op[i] == '*' && val[i]%2 == 0) type[i] = 2;
            count[type[i]]++;
        }

        visited = new boolean[2][2][count[0]+1][count[1]+1][count[2]+1];
        dp =      new boolean[2][2][count[0]+1][count[1]+1][count[2]+1];

        int cur = sc.nextInt() % 2;

        boolean odd = win(1, cur, count[0], count[1], count[2]);
        System.out.println(odd ? "me" : "you");
        System.out.flush();

        boolean used[] = new boolean[n];
        for (int k = 0; k < n; k++) {
            int i = 0;
            if ((k%2 == 1) != odd) {
                int j = -1;
                if (count[0] > 0 && !win(odd ? 0 : 1, cur,   count[0]-1, count[1], count[2])) j = 0;
                if (count[1] > 0 && !win(odd ? 0 : 1, 1-cur, count[0], count[1]-1, count[2])) j = 1;
                if (count[2] > 0 && !win(odd ? 0 : 1, 0,     count[0], count[1], count[2]-1)) j = 2;

                while (type[i] != j || used[i]) i++;

                System.out.println(op[i] + " " + val[i]);
                System.out.flush();
            } else {
                char curOp = sc.next().charAt(0);
                int curVal = sc.nextInt();
                while (op[i] != curOp || val[i] != curVal) i++;
            }
            count[type[i]]--;
            used[i] = true;
            if (type[i] == 1) cur = 1-cur;
            if (type[i] == 2) cur = 0;
        }
    }

    public static void main(String[] args) {
        new Paul().run();
    }
}
