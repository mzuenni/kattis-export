import java.util.Scanner;

class ternary {
	int n;
	int notes[];
	
	long tune(int ref) {
		long res = 0;
		for (int i = 0; i < n; ++i) {
			res += Math.abs(ref - notes[i] + i);
		}
		
		// minimize function
		return -res;
	}
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);

		ternary t = new ternary();
		t.n = sc.nextInt();

		t.notes = new int[t.n];
		for(int i = 0; i < t.n; ++i) {
			t.notes[i] = sc.nextInt();
		}

		int l = -200010;
		int r = 200010;

		while (r - l > 1) {
			int mid = (r + l) / 2;
			
			if (t.tune(mid) < t.tune(mid + 1)) {
				l = mid;
			} else {
				r = mid;
			}
		}

		System.out.println(-t.tune(r));
}
}
