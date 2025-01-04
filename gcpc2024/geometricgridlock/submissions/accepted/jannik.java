import java.util.*;

public class jannik {
  static void no() {
    System.out.println("no");
    System.exit(0);
  }
  static boolean flip = false;
  static void output(String s) {
    System.out.println("yes");
    if (!flip) {
      System.out.println(s);
      System.exit(0);
    }
    String[] lines = s.split("\n");
    for (int i = 0; i < lines[0].length(); i++) {
      for (int j = 0; j < lines.length; j++)
        System.out.print(lines[j].charAt(i));
      System.out.println();
    }
    System.exit(0);
  }
  static String out = "";
  static void tile(int w, String[] lines) {
    for (String s : lines) {
      for (int i = 0; i < w / s.length(); i++)
        out += s;
      out += '\n';
    }
  }
  static String[] five = {
  	"NNNUU",
  	"YWNNU",
  	"YWWUU",
  	"YYWWL",
  	"YLLLL"
  };
  static boolean solve(int w, int h) {
    if (h == 0) return true;
  	if (h == 2) {
  		if (w == 5) return false;
  		out += "PP";
  		for (int i = 0; i < w / 5 - 1; i++)
  			out += (i % 2 != 0 ? "NNNY" : "NNYYYY");
  		out += ((w / 5) % 2 != 0 ? "PPP\n" : "PP\n");

  		out += "PPP";
  		for (int i = 0; i < w / 5 - 1; i++)
  			out += (i % 2 != 0 ? "NNYYYY" : "NNNY");
  		out += ((w / 5) % 2 != 0 ? "PP\n" : "PPP\n");
  	} else if (h == 3 || h == 7) {
  		tile(w, new String[]{
  			"UUFFP",
  			"UFFPP",
  			"UUFPP"
  		});
  		solve(w, h - 3);
  	} else if (h == 4) {
  		tile(w, new String[]{
  			"LNVVV",
  			"LNZZV",
  			"LNNZV",
  			"LLNZZ"
  		});
  	} else if (h == 6) {
  		for (int j = 0; j < 6; j++) {
  			for (int i = 0; i < w/5; i++) {
  				if (i % 2 != 0 ? (j == 0) : (j == 5))
  					out += "IIIII";
  				else
  					out += five[j - (i%2)];
  			}
  			out += '\n';
  		}
  	} else {
  		tile(w, five);
  		return solve(w, h - 5);
  	}

  	return true;
  }
  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    int h = in.nextInt();
    int w = in.nextInt();

    if ((w * h) % 5 != 0) no();
    flip = w % 5 != 0;
    if (flip) {
      int x = w;
      w = h;
      h = x;
    }

  	if (h == 1) {
  		if (w > 5) no();
  		output("IIIII");
  	}

  	if (!solve(w, h)) no();
  	output(out);
  }
}
