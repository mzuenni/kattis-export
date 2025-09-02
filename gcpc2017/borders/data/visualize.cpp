#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for (int i = (a); i < (b); i++)

double xmin = INT_MAX, xmax = INT_MIN;
double ymin = INT_MAX, ymax = INT_MIN;
int margin = 50;
double scale = 1;

void read_point(ifstream &in, double &x, double &y) {
	in >> x >> y;
	xmin = min(xmin,x);
	xmax = max(xmax,x);
	ymin = min(ymin,y);
	ymax = max(ymax,y);
}

void transform(double &x, double &y) {
	x = x-xmin, y = ymax-y;
	x *= scale, y *= scale;
	x += margin, y += margin;
}

void print_point(double x, double y, string col) {
	transform(x,y);
	printf("<circle cx=\"%f\" cy=\"%f\" r=\"7\" fill=\"%s\" />\n", x, y, col.c_str());
	//printf("<text x=\"%f\" y=\"%f\" fill=\"black\" ", x, y);
	//printf("font-size=\"20\" ");
	//printf("transform=\"translate(-22,-12)\">%s</text>\n", label.c_str());
}

void print_line(double x1, double y1, double x2, double y2) {
	transform(x1,y1), transform(x2,y2);
	printf("<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" ", x1, y1, x2, y2);
	printf("style=\"stroke:black;stroke-width:2.5\" />\n");
}

int main(int argc, char **argv) {
	ifstream in, ans;
	assert(argc >= 3);
	in.open(argv[1], ios_base::in);
	ans.open(argv[2], ios_base::in);
	
	int n; in >> n;
	vector<double> x(n), y(n);
	vector<int> c(n);
	
	FOR(i,0,n) {
		read_point(in,x[i],y[i]);
		in >> c[i];
	}

	vector<double> px[2], py[2];
	FOR(k,0,2) {
		int m; ans >> m;
		px[k].resize(m);
		py[k].resize(m);
		FOR(i,0,m) read_point(ans, px[k][i], py[k][i]);
	}
	
	scale = 924.0 / max(xmax-xmin, ymax-ymin);
	int height = 100 + scale*(ymax-ymin), width = 100 + scale*(xmax-xmin);

	printf("<svg height=\"%d\" width=\"%d\">\n", height, width);
	
	string cols[] = {"","blue","red","green"};
	FOR(i,0,n) print_point(x[i], y[i], cols[c[i]]);
	
	FOR(k,0,2) {
		int m = px[k].size();
		FOR(i,1,m+1) print_line(px[k][i-1], py[k][i-1], px[k][i%m], py[k][i%m]);
	}

	printf("</svg>\n");
}

