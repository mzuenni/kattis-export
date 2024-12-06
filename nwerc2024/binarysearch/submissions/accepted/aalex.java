import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class aalex {
  final int[] labels;
  final List<List<Integer>> adjnodes;
  final int heights[];  // =0: unseen, <0: in progress, >0: done

  aalex(int[] labels, List<List<Integer>> adjnodes) {
    this.labels = labels;
    this.adjnodes = adjnodes;
    heights = new int[2 * labels.length];
  }

  boolean dfs(int node) {
    heights[node] = -1;
    int h = 1;
    for (int i : adjnodes.get(node >> 1)) {
      if ((node & 1) == 0 && labels[i] != labels[node >> 1]) continue;
      if ((node & 1) != 0 && labels[i] == labels[node >> 1]) continue;
      int node2 = (i << 1) ^ (node & 1) ^ 1;
      if (heights[node2] < 0) return true;
      if (heights[node2] == 0 && dfs(node2)) return true;
      h = Math.max(h, heights[node2] + 1);
    }
    heights[node] = h;
    return false;
  }

  int getLength() {
    for (int i = 0; i < 2 * labels.length; ++i) {
      if (heights[i] > 0) continue;
      if (dfs(i)) return -1;
    }

    int lens[][] = new int[2][2];
    for (int i = 0; i < 2 * labels.length; ++i) {
      int a = i & 1;
      int b = labels[i >> 1] & 1;
      lens[a][b] = Math.max(lens[a][b], heights[i]);
    }

    return 1 + Math.min(Math.min(lens[0][0], lens[0][1]),
                        Math.min(lens[1][0], lens[1][1]));
  }

  public static void main(String[] args) throws IOException {
    BufferedReader reader =
      new BufferedReader(new InputStreamReader(System.in));

    String[] nm = reader.readLine().split(" ");
    int n = Integer.parseInt(nm[0]);
    int m = Integer.parseInt(nm[1]);

    int[] labels = Arrays.stream(reader.readLine().split(" "))
                       .mapToInt(Integer::parseInt)
                       .toArray();

    List<List<Integer>> adjnodes = new ArrayList<List<Integer>>(n);
    for (int i = 0; i < n; ++i) adjnodes.add(new ArrayList<Integer>());
    for (int i = 0; i < m; ++i) {
      String[] uv = reader.readLine().split(" ");
      int u = Integer.parseInt(uv[0]);
      int v = Integer.parseInt(uv[1]);
      --u;
      --v;
      adjnodes.get(u).add(v);
      adjnodes.get(v).add(u);
    }

    int len = (new aalex(labels, adjnodes)).getLength();
    if (len < 0) {
      System.out.println("infinity");
    } else {
      System.out.println(len);
    }
  }
}
