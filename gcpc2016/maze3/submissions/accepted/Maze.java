import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;

public class Maze {

	public static void main(String[] args) {
		BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
		try {
			String line = bf.readLine();
			String[] split = line.split(" ");
			int n = Integer.parseInt(split[0]);
			int m = Integer.parseInt(split[1]);
			ArrayList<Integer>[] adj = new ArrayList[n];
			ArrayList<Integer>[] labels = new ArrayList[n];
			for (int i = 0; i < n; i++) {
				adj[i] = new ArrayList<Integer>();
				labels[i] = new ArrayList<Integer>();
			}
			int[][] labelcount = new int[n][26];	// counts number of labels per vertex.
			for (int i = 0; i < m; i++) {
				line = bf.readLine();
				split = line.split(" ");
				int u = Integer.parseInt(split[0])-1;
				int v = Integer.parseInt(split[1])-1;
				int l = split[2].charAt(0)-65;
				adj[u].add(v);
				adj[v].add(u);
				labels[u].add(l);
				labels[v].add(l);
				labelcount[u][l]++;
				labelcount[v][l]++;
			}
			line = bf.readLine();	// label sequence
			int[] labelSeq = new int[line.length()];
			for (int i = 0; i < line.length(); i++) {
				labelSeq[i] = line.charAt(i)-65;
//				System.out.println(labelSeq[i]);
			}
			
			double[] probs = new double[n];
			double[] probsNew = new double[n];
			probs[0] = 100.0;	// initial probability
			
			for (int i = 0; i < labelSeq.length; i++) {
//				System.out.println("-----");
//				System.out.println(Arrays.toString(probs));
				int label = labelSeq[i];
//				System.out.println("label: "+label);
				for (int u = 0; u < n; u++) {
					if (labelcount[u][label] == 0 || u == n-1) {	// no open door or target room
						probsNew[u] = probs[u];
					}
					else
						probsNew[u] = 0.0;
				}
//				System.out.println("in "+Arrays.toString(probsNew));
				for (int u = 0; u < n-1; u++) {	// do not leave target room!
					if (labelcount[u][label] != 0) {	// open doors to adjacent rooms!
						double prob = 1.0/labelcount[u][label];
						for (int j = 0; j < adj[u].size(); j++) {
							if (labels[u].get(j) == label) {
								
								int v = adj[u].get(j);
//								System.out.println(u+": door to "+v+" open.");
								probsNew[v] += probs[u]*prob;
							}
						}
					}
				}
//				System.out.println(Arrays.toString(probsNew));
				double[] tmp = probs;
				probs = probsNew;
				probsNew = tmp;
				Arrays.fill(probsNew, 0.0);
			}
			System.out.println(probs[n-1]);
			
			bf.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
		
	}
}
