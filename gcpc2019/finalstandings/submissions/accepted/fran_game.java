import java.util.Scanner;

public class fran_game {
	
	public static void main(String[] args) {
		Scanner reader = new Scanner(System.in);
		t = reader.nextInt();
		p = reader.nextInt();
		S = new double[t - 1];
		for(int i = 0; i < S.length; i++) {
			S[i] = reader.nextDouble();
		}
		D = new double[p];
		for(int i = 0; i < D.length; i++) {
			D[i] = reader.nextDouble();
		}
		C = new char[t - 1][p];
		for(int i = 0; i < t - 1; i++) {
			for(int j = 0; j < p; j++) {
				C[i][j] = reader.next().charAt(0);
			}
		}
		solvedTeam = 0;
		for(int i = 0; i < p; i++) {
			char c = reader.next().charAt(0);
			if(c == 'X') {
				solvedTeam += 1;
			}
		}
		double probWin = 1;
		for(int i = 0; i < t - 1; i++) {
			memo = new Double[p][p];
			double p = prob(0, 0, i);
			probWin *= (1 - p);
		}
		System.out.println(probWin);
		reader.close();
	}

	static int t, p;
	static char[][] C;
	static double[] S;
	static double[] D;
	static int solvedTeam;
	
	static Double[][] memo;

	static double prob(int problem, int solved, int team) {
		if(problem == p) {
			return solved > solvedTeam ? 1.0 : 0.0;
		}
		if(memo[problem][solved] != null) {
			return memo[problem][solved];
		}
		if(C[team][problem] == '-') {
			memo[problem][solved] = prob(problem + 1, solved, team);
		} else if(C[team][problem] == 'X') {
			memo[problem][solved] = prob(problem + 1, solved + 1, team);
		} else {
			double probSolve = S[team] * D[problem];			
			memo[problem][solved] = (1 - probSolve) * prob(problem + 1, solved, team) + probSolve * prob(problem + 1, solved + 1, team);
		}
		return memo[problem][solved];
	}

}
