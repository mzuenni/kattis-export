#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>
#include <sstream>
#include <stack>
#include <queue>
#include <map>
#include <climits>
#include <cstdio>
#include <set>
#include <array>
#include <unordered_map>
#include <unordered_set>
#include <iomanip>
#include <functional>
#include <random>
using namespace std;
#define db(a) (cout << (#a) << " = " << (a) << endl)
typedef long long ll;

int N;
struct point
{
	double x,y;
	int c;
	bool operator<(const point& b)
	{
		if(x==b.x) return y<b.y;
		return x<b.x;
	}
};

vector<point> points;
vector<pair<double,double>> vert0;
vector<pair<double,double>> vert1;

bool eq(double a, double b)
{
	return abs(a-b) < 0.000001;
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  default_random_engine generator;
  uniform_real_distribution<double> distribution(0.0,2.0*acos(-1.0));
  auto random_radian = [&](){return distribution(generator);};
  
  random_radian();random_radian();
  
  cin>>N;
	for(int i=0;i<N;i++)
	{
		double x,y;
		int c;
		cin>>x>>y>>c;
		c--;
		points.push_back({x,y,c});
	}
	double angle = 0.0;
	while(true)
	{
		sort(points.begin(), points.end());
		bool duplicate = false;
		for(size_t j=1;j<points.size();j++) if(eq(points[j-1].x, points[j].x)) duplicate = true;
		if(!duplicate) break;
		angle = random_radian();
		for(size_t j=0;j<points.size();j++)
		{
			double x = points[j].x;
			double y = points[j].y;
			points[j].x = x*cos(angle) - y*sin(angle);
			points[j].y = x*sin(angle) + y*cos(angle);
		}
	}
	
	double maxv = 1414.0;
	double amaxv = maxv-10.0;
	double hmaxv = maxv-100.0;
	
	vert0.push_back({-amaxv,-amaxv});
	for(size_t i=0;i<points.size();i++)
	{
		if(points[i].c != 0) continue;
		double last = -amaxv;
		if(i>0) last = points[i-1].x;
		double offset = abs(points[i].x-last)/3.0;
		vert0.push_back({points[i].x - offset, -amaxv});
		vert0.push_back({points[i].x - offset, hmaxv});
		double next = amaxv;
		if(i+1<points.size()) next = points[i+1].x;
		offset = abs(points[i].x-next)/3.0;
		vert0.push_back({points[i].x + offset, hmaxv});	
		vert0.push_back({points[i].x + offset, -amaxv});		
	}
	vert0.push_back({amaxv,-amaxv});
	vert0.push_back({amaxv,-maxv});
	vert0.push_back({-amaxv,-maxv});
	
	vert1.push_back({-amaxv,amaxv});
	for(size_t i=0;i<points.size();i++)
	{
		if(points[i].c != 1) continue;
		double last = -amaxv;
		if(i>0) last = points[i-1].x;
		double offset = abs(points[i].x-last)/3.0;
		vert1.push_back({points[i].x - offset, amaxv});
		vert1.push_back({points[i].x - offset, -hmaxv});
		double next = amaxv;
		if(i+1<points.size()) next = points[i+1].x;
		offset = abs(points[i].x-next)/3.0;
		vert1.push_back({points[i].x + offset, -hmaxv});	
		vert1.push_back({points[i].x + offset, amaxv});		
	}
	vert1.push_back({amaxv,amaxv});
	vert1.push_back({amaxv,maxv});
	vert1.push_back({-amaxv,maxv});
	
	for(size_t j=0;j<vert0.size();j++)
	{
		double x = vert0[j].first;
		double y = vert0[j].second;
		vert0[j].first = x*cos(angle) + y*sin(angle);
		vert0[j].second = -x*sin(angle) + y*cos(angle);
	}
	for(size_t j=0;j<vert1.size();j++)
	{
		double x = vert1[j].first;
		double y = vert1[j].second;
		vert1[j].first = x*cos(angle) + y*sin(angle);
		vert1[j].second = -x*sin(angle) + y*cos(angle);
	}
	
	//db(angle);
	
	cout << vert0.size() << "\n";
	for(const auto& p : vert0) cout << fixed << setprecision(3) << p.first << " " << p.second << "\n";
	cout << vert1.size() << "\n";
	for(const auto& p : vert1) cout << fixed << setprecision(3) << p.first << " " << p.second << "\n";
	
  return 0;
}

