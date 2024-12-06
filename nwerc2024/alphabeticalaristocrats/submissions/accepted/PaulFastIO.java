import java.io.*;
import java.util.*;
import java.util.stream.*;

public class PaulFastIO {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(br.readLine());

        String[] names = new String[n];
        for (int i = 0; i < n; i++) {
            names[i] = br.readLine();
        }
        Arrays.sort(names, Comparator.comparing(
            s -> s.substring(
                IntStream.range(0, s.length())
                .filter(i -> Character.isUpperCase(s.charAt(i)))
                .findFirst()
                .getAsInt()
            )
        ));

        PrintWriter pw = new PrintWriter(System.out);
        for (String s: names) {
            pw.println(s);
        }
        pw.close();
    }
}
