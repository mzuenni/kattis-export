// @EXPECTED_RESULTS@: TIMELIMIT

import java.io.*;
import java.util.*;
import java.text.*;

public class tobi2 {

	public static final String start = "2012-12-31";
	public static final String startH = "23:59";
	public static final String end = "2017-01-02";
	public static final String endH = "00:00";
	public static DateFormat formatter = new SimpleDateFormat("yyyy-MM-dd HH:mm");
	public static long getTime(String dateS, String timeS) throws Exception {
		Date date = formatter.parse(dateS + " " + timeS);
		Calendar calendar = Calendar.getInstance();
		calendar.setTime(date);
		return calendar.getTimeInMillis() / 1000;
	}

	public static int array[];

	public static void main(String args[]) throws Exception {
		Scanner sc = new Scanner(System.in);
		long s = getTime(start, startH);
		long e = getTime(end, endH);
		array = new int[(int) (e - s + 1)];

		int numCases = sc.nextInt();
		while (numCases --> 0) {
			Arrays.fill(array, 0);
			int numBookings = sc.nextInt();
			int cleanTime = sc.nextInt();
			for (int i = 0; i < numBookings; i++) {
				String tmp = sc.next();

				int before = (int) getTime(sc.next(), sc.next());
				int after = (int) (getTime(sc.next(), sc.next()) + cleanTime * 60);
				before -= (int) s;
				after -= (int) s;
				for (int j = before; j < after; j++) {
					array[j]++;
				}
			}
			int maxRooms = 0;
			for (int i = 0; i < array.length; i++) {
				maxRooms = Math.max(maxRooms, array[i]);
			}
			System.out.println(maxRooms);
		}
	}
}
