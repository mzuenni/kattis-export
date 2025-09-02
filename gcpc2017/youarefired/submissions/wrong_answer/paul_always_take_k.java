import java.util.*;

class Employee implements Comparable<Employee> {
	String name;
	int salary;

	public Employee(String name, int salary) {
		this.name = name;
		this.salary = salary;
	}

	public int compareTo(Employee other) {
		return Integer.compare(other.salary, salary);
	}
}

public class paul_always_take_k {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt(), d = sc.nextInt(), k = sc.nextInt();

		Employee[] employees = new Employee[n];
		for (int i = 0; i < n; i++)
			employees[i] = new Employee(sc.next(), sc.nextInt());

		Arrays.sort(employees);
		
		int totalSavings = 0;
		for (int i = 0; i < k; i++) {
			totalSavings += employees[i].salary;
		}

		if (totalSavings < d) {
			System.out.println("impossible");
		} else {
			System.out.println(k);
			for (int i = 0; i < k; i++)
				System.out.println(employees[i].name + ", YOU ARE FIRED!");
			return;
		}
	}
}
