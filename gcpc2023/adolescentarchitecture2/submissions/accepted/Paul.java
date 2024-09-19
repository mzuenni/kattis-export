import java.io.*;
import java.math.*;
import java.util.*;

public class Paul {
	static final MathContext mc = MathContext.DECIMAL128;
	static final BigDecimal one = new BigDecimal(1);
	static final BigDecimal two = new BigDecimal(2);
	static final BigDecimal three = new BigDecimal(3);
	static final BigDecimal almostOne = one.subtract(new BigDecimal(1e-22));
	
	static BigDecimal sqrt(BigDecimal x) {
		BigDecimal y = BigDecimal.ONE;
		for (int i = 0; i < 10; i++) {
			y = y.add(x.divide(y, mc)).divide(two);
		}
		return y;
	}

	public enum Shape { CIRCLE, SQUARE, TRIANGLE };

	class Block {
		Shape shape;
		int size;

		static final BigDecimal[][] scale = {
			{almostOne, sqrt(two), sqrt(three)},
			{almostOne.divide(two), almostOne, sqrt(two).multiply(sqrt(three).subtract(one))},
			{one.divide(two.multiply(sqrt(three)), mc), two.multiply(sqrt(three)).subtract(three), almostOne}
		};

		public Block(Shape shape, int size) {
			this.shape = shape;
			this.size = size;
		}

		public int largestInsideFit(Shape shape) {
			BigDecimal conv = scale[this.shape.ordinal()][shape.ordinal()];
			BigDecimal size = new BigDecimal(this.size).multiply(conv);
			return size.setScale(0, RoundingMode.DOWN).intValue();
		}

		public int smallestOutsideFit(Shape shape) {
			BigDecimal conv = scale[shape.ordinal()][this.shape.ordinal()];
			BigDecimal size = new BigDecimal(this.size).divide(conv, mc);
			return size.setScale(0, RoundingMode.UP).intValue();
		}

		public int grundyValue() {
			if (this.shape == Shape.CIRCLE && this.size == 1) {
				return 2;
			} else {
				return largestInsideFit(Shape.TRIANGLE);
			}
		}
	}

	int sizeForGrundyValue(Shape shape, int value) {
		if (shape == Shape.TRIANGLE) return value + 1;
		if (shape == Shape.CIRCLE && value == 2) return 1;
		int size = new Block(Shape.TRIANGLE, value).smallestOutsideFit(shape);
		return new Block(shape, size).grundyValue() == value ? size : 0;
	}

	void solve() throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(br.readLine()); 
		Block[] blocks = new Block[n];
		for (int i = 0; i < n; i++) {
			var tokens = br.readLine().split(" ");
			Shape shape;
			if (tokens[0].equals("circle")) {
				shape = Shape.CIRCLE;
			} else if (tokens[0].equals("square")) {
				shape = Shape.SQUARE;
			} else {
				shape = Shape.TRIANGLE;
			}
			blocks[i] = new Block(shape, Integer.parseInt(tokens[1]));
		}

		int totalGrundyValue = 0;
		for (Block block: blocks) {
			totalGrundyValue ^= block.grundyValue();
		}

		int count = 0;
		for (Block block: blocks) {
			int remainingGrundyValue = totalGrundyValue ^ block.grundyValue();
			for (Shape shape: Shape.values()) {
				int size = sizeForGrundyValue(shape, remainingGrundyValue);
				if (size != 0 && size <= block.largestInsideFit(shape)) count++;
			}
		}
		System.out.println(count);
	}

	public static void main(String[] args) throws Exception {
		new Paul().solve();
	}
}
