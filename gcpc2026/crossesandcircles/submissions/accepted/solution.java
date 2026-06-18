import java.io.PrintWriter;
import java.util.Scanner;

class solution {
    static final Scanner in = new Scanner(System.in);
    static final PrintWriter out = new PrintWriter(System.out);

    static int[] move(int r, int c) {
        out.println(r + " " + c);
        out.flush();

        int x = in.nextInt();
        int y = in.nextInt();
        if (x == 0 && y == 0) {
            System.exit(0);
        }
        return new int[] {x, y};
    }

    public static void main(String[] args) throws Exception {
        int[] first = move(7, 7);
        if (first[0] == 7) {
            int[] second = move(6, 7);
            move(second[0] == 5 ? 8 : 5, 7);
        } else {
            int[] second = move(7, 6);
            move(7, second[1] == 5 ? 8 : 5);
        }
    }
}
