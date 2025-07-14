import java.util.*;

public class Paul {
    static class Complex {
        double real, imag;

        public Complex(double real, double imag) {
            this.real = real;
            this.imag = imag;
        }

        double dot(Complex c) { return real*c.real + imag*c.imag; }
        double cross(Complex c) { return real*c.imag - imag*c.real; }
        double abs() { return Math.hypot(real, imag); }
        Complex add(Complex c) { return new Complex(real+c.real, imag+c.imag); }
        Complex subtract(Complex c) { return new Complex(real-c.real, imag-c.imag); }
        Complex multiply(Complex c) {
            return new Complex(real*c.real - imag*c.imag, real*c.imag + imag*c.real);
        }
        Complex multiply(double t) { return new Complex(t*real, t*imag); }
        Complex divide(double t) { return new Complex(real/t, imag/t); }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();

        Complex[] ps = new Complex[n];
        for (int i = 0; i < n; i++) {
            double x = sc.nextInt();
            double y = sc.nextInt();
            ps[i] = new Complex(x, y);
        }

        double res = 0;
        for (int i = 0; i < n; i++) {
            Complex a = ps[(i+n-2)%n], b = ps[(i+n-1)%n], c = ps[i];
            Complex d = ps[(i+1)%n], e = ps[(i+2)%n], j = new Complex(0, 1);
            Complex u = b.subtract(a), v = d.subtract(b), w = e.subtract(d), z;
            if (u.cross(v) == 0 && v.cross(w) == 0) {
                continue;
            } else if (u.dot(v) > 0 && v.dot(w) > 0 && u.dot(w) > 0) {
                z = a.add(u.multiply(d.subtract(a).cross(w) / u.cross(w)));
            } else if (u.dot(v) >= u.cross(v)) {
                z = b.add(u.multiply(u.dot(v) / u.dot(u)));
            } else if (-u.dot(v) >= u.cross(v)) {
                z = b.add(u.multiply(u.cross(v) / u.dot(u)).multiply(j));
            } else if (v.dot(w) >= v.cross(w)) {
                z = d.subtract(w.multiply(v.dot(w) / w.dot(w)));
            } else if (-v.dot(w) >= v.cross(w)) {
                z = d.add(w.multiply(v.cross(w) / w.dot(w)).multiply(j));
            } else {
                z = b.add(v.multiply(new Complex(0.5, -0.5)));
            }
            double add = z.subtract(b).abs() + z.subtract(d).abs();
            double sub = c.subtract(b).abs() + c.subtract(d).abs();
            res = Math.max(res, add-sub);
        }
        System.out.format("%.10f\n", res);
    }
}
