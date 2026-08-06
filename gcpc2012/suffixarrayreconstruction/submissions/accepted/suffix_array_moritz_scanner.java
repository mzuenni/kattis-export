// @EXPECTED_RESULTS@: CORRECT
import java.util.*;

public class suffix_array_moritz_scanner {
	public static final int MAXN = 100000;
	public static char reconstructed[];
	public static boolean set[];
	
	public static void main( String[] args ) {
		Scanner scanner = new Scanner( System.in );
		int cases = scanner.nextInt();
		
		reconstructed = new char[MAXN+1];
		set = new boolean[MAXN+1];
				
		for( int i = 0; i < cases; ++i ){
			int length, suffixes;
			length = scanner.nextInt();
			suffixes = scanner.nextInt();
			boolean conflict = false;
			for( int l = 0; l < length; ++l ){
				set[l] = false;
				reconstructed[l] = ' ';
			}
			for( int s = 0; s < suffixes; ++s ){
				int position = scanner.nextInt() - 1;
				String suffix = scanner.next();
				for( int p = 0; p < suffix.length(); ++p ){
					if( suffix.charAt(p) == '*' )
						break;
					if( !set[position+p] ){
						set[position+p] = true;
						reconstructed[position+p] = suffix.charAt(p);
					}
					if( suffix.charAt(p) != reconstructed[position+p] ){
						conflict = true;
					}
				}
				for( int p = 0; p < suffix.length(); ++p ){
					int pos = suffix.length() - 1 - p;
					if( suffix.charAt(pos) == '*' )
						break;
					if( !set[length-1-p] ){
						set[length-1-p] = true;
						reconstructed[length-1-p] = suffix.charAt(pos);
					}
					if( suffix.charAt(pos) != reconstructed[length-1-p] ){
						conflict = true;
					}
				}
			}
			for( int l = 0; l < length; ++l ){
				if( !set[l] ){
					conflict = true;
					break;
				}
			}
			if( conflict ){
				System.out.println("IMPOSSIBLE");
			} else {
				for( int l = 0; l < length; ++l )
					System.out.print(reconstructed[l]);
				System.out.println();
			}
		}
	}
}

