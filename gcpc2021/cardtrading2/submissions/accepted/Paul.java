import java.util.*;
import java.math.*;

public class Paul {
	static class PricePoint implements Comparable<PricePoint> {
		int price, buyOffers, sellOffers;

		PricePoint(int price, int buyOffers, int sellOffers) {
			this.price = price;
			this.buyOffers = buyOffers;
			this.sellOffers = sellOffers;
		}
		
		public int compareTo(PricePoint p) {
			return Integer.compare(price, p.price);
		}
	}

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);

		int n = sc.nextInt();
		long totalSales = 0, totalBuys = 0;
		PricePoint[] pricePoints = new PricePoint[n];
		for (int i = 0; i < n; i++) {
			int price = (int) Math.round(100*sc.nextDouble());
			int buyOffers = sc.nextInt();
			int sellOffers = sc.nextInt();
			pricePoints[i] = new PricePoint(price, buyOffers, sellOffers);
			totalBuys += buyOffers;
		}
		Arrays.sort(pricePoints);

		long bestTurnover = 0, bestPrice = 0;
		for (PricePoint p: pricePoints) {
			totalSales += p.sellOffers;

			long curTurnover = p.price * Math.min(totalBuys, totalSales);
			if (curTurnover > bestTurnover) {
				bestTurnover = curTurnover;
				bestPrice = p.price;
			}

			totalBuys -= p.buyOffers;
		}
		
		if (bestTurnover > 0) {
			BigDecimal price = new BigDecimal(BigInteger.valueOf(bestPrice), 2);
			BigDecimal turnover = new BigDecimal(BigInteger.valueOf(bestTurnover), 2);
			System.out.println(price.toPlainString() + " " + turnover.toPlainString());
		} else {
			System.out.println("impossible");
		}
	}
}
