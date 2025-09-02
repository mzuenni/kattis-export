import java.io.*;
import java.util.*;
import java.util.stream.*;

import static java.util.function.Predicate.isEqual;
import static java.util.stream.Collectors.*;

public class rgl {
    enum Cell {
        SOLVED("X"), UNSOLVED("-"), PENDING("?");
        public final String code;
        private Cell(String c) {code = c;}
    }

    private static final Map<String, Cell> cellMap = Arrays.stream(Cell.values())
            .collect(toMap(x -> x.code, x -> x));

    private interface Team {
        double getChance(int solved);

        default double getChanceUpTo(int score) {
            return IntStream.rangeClosed(0, score).mapToDouble(this::getChance).sum();
        }

        default int getFirstScore() {
            return IntStream.iterate(0, x -> x+1)
                    .filter(x -> getChance(x) > 0).findFirst().orElse(0);
        }
    }

    private static Team parseTeam(String line, double strength, List<Double> difficulties) {
        final List<Cell> cells = Arrays.stream(line.split(" ")).map(cellMap::get).collect(toList());

        final int correct = (int) cells.stream().filter(isEqual(Cell.SOLVED)).count();
        final double[] dp = new double[cells.size() + 1];
        dp[correct] = 1.0;

        IntStream.range(0, cells.size())
                .filter(x -> cells.get(x) == Cell.PENDING)
                .mapToDouble(x -> strength * difficulties.get(x))
                .forEach(chance -> {
                    for (int j = dp.length; j --> correct;) {
                        dp[j] = dp[j] * (1 - chance) + (j > 0 ? dp[j-1] : 0.0) * chance;
                    }
                });
        return (int solved) -> (0 <= solved && solved < dp.length ? dp[solved] : 0.0);
    }

    public static void main(String[] args) throws Exception {
        final BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        final String[] firstLine = br.readLine().split(" ");
        final int t = Integer.parseInt(firstLine[0]);
        final int p = Integer.parseInt(firstLine[1]);

        final List<Double> strengths = Arrays.stream(br.readLine().split(" "))
                .limit(t - 1)
                .map(Double::parseDouble)
                .collect(toList());
        final List<Double> difficulties = Arrays.stream(br.readLine().split(" "))
                .limit(p)
                .map(Double::parseDouble)
                .collect(toList());
        final List<String> teamLines = IntStream.range(0, t-1)
                .mapToObj(i -> {try {return br.readLine();} catch (Exception e) {return "";}})
                .collect(toList());
        final List<Team> teams = IntStream.range(0, t-1)
                .mapToObj(i -> parseTeam(teamLines.get(i), strengths.get(i), difficulties))
                .collect(toList());

        final int scoreToBeat = parseTeam(br.readLine(), 1.0, difficulties).getFirstScore();
        System.out.format("%.8f%n", teams.stream()
                .mapToDouble(x -> x.getChanceUpTo(scoreToBeat))
                .reduce((a, b) -> a * b)
                .orElse(1.0));
    }
}
