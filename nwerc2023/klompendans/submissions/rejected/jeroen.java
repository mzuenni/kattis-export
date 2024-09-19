// @EXPECTED_RESULTS@: RUN_TIME_ERROR, TIME_LIMIT_EXCEEDED
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;
import java.awt.*;

public class jeroen {
	static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

	public static void main(String[] args) throws Exception {
		// Read input
		int n = Integer.valueOf(in.readLine());
		int[] dx = new int[2];
		int[] dy = new int[2];
		for(int i = 0; i < 2; i++) {
			String[] ps = in.readLine().split(" ");
			dx[i] = Integer.valueOf(ps[0]);
			dy[i] = Integer.valueOf(ps[1]);
		}

		// BFS
		boolean[][][] visited = new boolean[n][n][2];
		Queue<State> q = new LinkedList<State>();
		q.add(new State(0,0,0));
		q.add(new State(0,0,1));
		while(!q.isEmpty()) {
			State p = q.poll();
			if(p.x < 0 || p.x >= n || p.y < 0 || p.y >= n) continue;
			//if(visited[p.x][p.y][p.m]) continue;
			visited[p.x][p.y][p.m] = true;
			q.add(new State(p.x + dx[p.m], p.y + dy[p.m], 1 - p.m));
			q.add(new State(p.x - dx[p.m], p.y + dy[p.m], 1 - p.m));
			q.add(new State(p.x + dx[p.m], p.y - dy[p.m], 1 - p.m));
			q.add(new State(p.x - dx[p.m], p.y - dy[p.m], 1 - p.m));
			q.add(new State(p.x + dy[p.m], p.y + dx[p.m], 1 - p.m));
			q.add(new State(p.x - dy[p.m], p.y + dx[p.m], 1 - p.m));
			q.add(new State(p.x + dy[p.m], p.y - dx[p.m], 1 - p.m));
			q.add(new State(p.x - dy[p.m], p.y - dx[p.m], 1 - p.m));
		}

		// Count
		int ans = 0;
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				if(visited[i][j][0] || visited[i][j][1])
					ans++;
		System.out.println(ans);
	}

	static class State {
		public int x, y, m;
		public State(int x, int y, int m) {
			this.x = x;
			this.y = y;
			this.m = m;
		}
	}
}
