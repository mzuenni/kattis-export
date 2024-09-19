import java.util.Scanner;
import java.lang.StringBuilder;

public class MarcelWA8 {

    public static void main(String[] args) {
	Scanner s = new Scanner(System.in);

	String query = "";

	for(int i = 0; i < 26; ++i) {
	    query += (char) ('a' + i);
	}

	System.out.println("? " + query);
	System.out.flush();

	int n = s.nextInt();
	int length = 0;
	for(int i = 0; i < n; ++i) {
	    length = Math.max(length, s.nextInt());
	}

	query = "";

	for(int i = 0; i < 26; ++i) {
	    query += (char) ('a' + i);
	}

	System.out.println("? " + query);
	System.out.flush();

	n = s.nextInt();
	length = 0;
	for(int i = 0; i < n; ++i) {
	    length = Math.max(length, s.nextInt());
	}

	boolean[][] possChars = new boolean[26][length];
	for(int i = 0; i < 26; ++i) {
	    for(int j = 0; j < length; ++j) {
		possChars[i][j] = true;
	    }
	}
	
	for(int i = 0; i < 5; ++i) {
	    query = "";
	    for(int j = 0; j < 26; ++j) {
		if((j & (1 << i)) != 0) {
		    query += (char) ('a' + j);
		}
	    }
	    System.out.println("? " + query);
	    System.out.flush();

	    n = s.nextInt();
	    boolean[] pos = new boolean[length];
	    for(int rep = 0; rep < n; ++rep) {
		int p = s.nextInt();
		pos[p-1] = true;
	    }
	    for(int p = 0; p < length; ++p) {
		for(int c = 0; c < 26; ++c) {
		    if(!pos[p] && (c & (1 << i)) != 0) {
			possChars[c][p] = false;
		    }
		    if(pos[p] && (c & (1 << i)) == 0) {
			possChars[c][p] = false;
		    }
		}
	    }
	}
	StringBuilder out = new StringBuilder();
	
	for(int i = 0; i < length; ++i) {
	    for(int j = 0; j < 26; ++j) {
		if(possChars[j][i]) {
		    out.append((char) ('a' + j));
		}
	    }
	}
	
	System.out.println("! " + out.toString());
    }
    
}
