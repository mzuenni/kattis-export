import java.io.*;
import java.util.*;

public class PaulDouble {
	public enum Shape { CIRCLE, SQUARE, TRIANGLE };
	
	class Block {
		Shape shape;
		int size;

		static final double[][] scale = {
			{1, Math.sqrt(2), Math.sqrt(3)},
			{0.5, 1, Math.sqrt(6)-Math.sqrt(2)},
			{1/Math.sqrt(12), Math.sqrt(12)-3, 1}
		};

		public Block(Shape shape, int size) {
			this.shape = shape;
			this.size = size;
		}

		public int largestInsideFit(Shape shape) {
			double conv = scale[this.shape.ordinal()][shape.ordinal()];
			conv *= 1 - 1e-15;
			return (int) Math.floor(this.size * conv);
		}

		public int smallestOutsideFit(Shape shape) {
			double conv = scale[shape.ordinal()][this.shape.ordinal()];
			conv *= 1 - 1e-15;
			return (int) Math.ceil(this.size / conv);
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
		new PaulDouble().solve();
	}
}
