import java.util.ArrayList;
import java.util.Scanner;

public class WrongComparison_NoJE {
	static class Employee {
		String name;
		Integer sal;
		public Employee(String name, int sal) {
			this.name = name;
			this.sal = sal;
		}
	}
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		int n = sc.nextInt();
		int d = sc.nextInt();
		int k = sc.nextInt();
		
		ArrayList<Employee> list = new ArrayList<>();
		for (int i = 0; i < n; i++) {
			list.add(new Employee(sc.next(), sc.nextInt()));
		}
		list.sort((one, two) -> two.sal.compareTo(one.sal));
		int sum = 0;
		int people = 0;
		while (sum < d && people <= k) {
			sum += list.get(people).sal;
			people++;
		}
		if (sum < d) {
			System.out.println("impossible");
		} else {
			System.out.println(people);
			for (int i = 0; i < people; i++) {
				System.out.println(list.get(i).name + ", YOU ARE FIRED!");
			}
		}
		sc.close();
	}
}
