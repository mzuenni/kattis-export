import java.util.*;

public class Michaelr{
    private static Scanner s;

    static int n, m;
    static Connection[] cons;
    static int[] distances;

    public static void main(String[] args){
        s = new Scanner(System.in);

        n = s.nextInt();
        m = s.nextInt();

        distances = new int[n];
        for(int i=1; i<n; i++) distances[i] = -1;
        cons = new Connection[m];

        for(int i=0; i<m; i++) cons[i] = new Connection(s.nextInt(), s.nextInt(), s.nextInt());

        Arrays.sort(cons, (a, b) -> new Integer(b.w).compareTo(a.w));

        int r = s.nextInt();
        Request[] requests = new Request[r];
        Request[] sortedRequests = new Request[r];

        for(int i=0; i<r; i++) requests[i] = new Request(i, s.nextInt());
        for(int i=0; i<r; i++) sortedRequests[i] = requests[i];

        Arrays.sort(sortedRequests, (a, b) -> new Integer(b.w).compareTo(a.w));

        int blocked = n-1;
        int currentTotal = 0;
        int cur = 0;
        for(Request req : sortedRequests){
            for(;cur < cons.length && cons[cur].w >= req.w; cur++){
                Connection c = cons[cur];
                if(distances[c.i] < 0) {
                    blocked --;
                    currentTotal += c.d;
                } else if(distances[c.i] > c.d){
                    currentTotal += c.d - distances[c.i];
                }
                distances[c.i] = c.d;
            }

            if(blocked > 0) req.res = -1;
            else req.res = currentTotal;
        }

        for(Request req : requests)
            if(req.res < 0) System.out.println("impossible");
            else System.out.println(req.res);
    }

    static class Request{
        int id, w, res;
        public Request(int id, int w){
            this.id = id;
            this.w = w;
        }
    }

    static class Connection{
        int i, d, w;

        public Connection(int i, int d, int w){
            this.i = i;
            this.d = d;
            this.w = w;
        }
    }
}