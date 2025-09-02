import java.awt.*;
import java.util.LinkedList;
import java.util.Random;
import java.util.Scanner;

public class BoulderingGenerator {

    public static void main(String[] args) {

        var sc = new Scanner(System.in);

        var rand = new Random(sc.nextLong());

        int xdim = sc.nextInt() -1;
        int ydim = sc.nextInt() -1;

        int rmin = sc.nextInt();
        int rmax = sc.nextInt();

        int smin = sc.nextInt();
        int smax = sc.nextInt();

        int stepsmin = sc.nextInt();
        int stepsmax = sc.nextInt();

        int mode = sc.nextInt();

        int[][] field = new int[xdim + 1][ydim + 1];

        var r = roll(rand, rmin, rmax);
        var s = roll(rand, smin, smax);

        switch (mode) {
            case 0:
//                all ks, entry bottom left, exit top right
                field[xdim][ydim] = 1;
                field[0][0] = 1;
                for (int x = 0; x <= xdim; x++) {
                    for (int y = 1; y < ydim; y++) {
                        field[x][y] = roll(rand, stepsmin, stepsmax);
                    }
                }
                break;
            case 1: {
//                generate reachables
                double fill = sc.nextDouble();
                int n = (int) Math.floor(xdim * (ydim - 1) * fill);

                for (int i = 0; i < n; i++) {
                    int x = roll(rand, 0, xdim);
                    int y = roll(rand, 0, ydim);
                    if (field[x][y] == 0 && reachable(field, new Point(x, y), r)) {
                        field[x][y] = roll(rand, stepsmin, stepsmax);
                    } else {
                        i--;
                    }
                }
            }
            break;
            case 2: {
//                full random
                double fill = sc.nextDouble();
                int n = (int) Math.floor(xdim * (ydim - 1) * fill);

                for (int i = 0; i < n; i++) {
                    int x = roll(rand, 0, xdim);
                    int y = roll(rand, 0, ydim);
                    if (field[x][y] == 0) {
                        field[x][y] = roll(rand, stepsmin, stepsmax);
                    } else {
                        i--;
                    }
                }
            }
            break;
        }

//        check for multiple inits/targets
        boolean foundmax = false;
        for (int y = ydim; y >= 0; y--) {
            for (int x = 0; x <= xdim; x++) {
                if (field[x][y] != 0) {
                    if (foundmax) {
                        field[x][y] = 0;
                    } else {
                        foundmax = true;
                    }
                }
            }
            if (foundmax) {
                break;
            }
        }
        boolean foundmin = false;
        for (int y = 0; y <= ydim; y++) {
            for (int x = xdim; x >= 0; x--) {
                if (field[x][y] != 0) {
                    if (foundmin) {
                        field[x][y] = 0;
                    } else {
                        foundmin = true;
                    }
                }
            }
            if (foundmin) {
                break;
            }
        }

        var casestring = new StringBuilder();
        casestring.append(ydim + 1).append(" ").append(xdim + 1).append(" ").append(r).append(" ").append(s).append("\n");
        for (int y = ydim; y >= 0; y--) {
            for (int x = 0; x <= xdim; x++) {
                casestring.append(field[x][y] == 0 ? "." : field[x][y]);
            }
            casestring.append("\n");
        }

        System.out.print(casestring);
    }

    static boolean reachable(int[][] field, Point newpoint, int r) {
        if (newpoint.y <= r) {
            return true;
        }
        for (int y = newpoint.y - r; y <= newpoint.y + r; y++) {
            for (int x = newpoint.x - r; x <= newpoint.x + r; x++) {
                if (x > 0 && y > 0 && x < field.length && y < field[0].length && field[x][y] != 0 &&
                        newpoint.distance(new Point(x, y)) < r) {
                    return true;
                }
            }
        }
        return false;
    }


    public static int roll(Random r, int min, int max) {
        return min + r.nextInt(max - min + 1);
    }
}
