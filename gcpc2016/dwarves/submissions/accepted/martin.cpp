#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string>
#include <map>
#include <vector>

using namespace std;

int main () {
    int n;
    scanf("%d\n", &n);
    map<string,int> dwarves;
    int dwarve_count=0;
    vector< vector<int> > tallers;
    for (int i=0;i<n;i++) {
	char a[100];
	char b[100];
	char c[100];
	scanf("%s %s %s\n",a,c,b);
	string as,bs,cs;
	as=a;
	bs=b;
        cs=c;
        if (cs=="<") {
            swap(as,bs);
        }
	if (dwarves.count(as)==0) {
	    dwarves[as]=dwarve_count++;
            vector<int> nd;
            tallers.push_back(nd);
	}
	if (dwarves.count(bs)==0) {
	    dwarves[bs]=dwarve_count++;
            vector<int> nd;
            tallers.push_back(nd);
	}
	tallers[dwarves[as]].push_back(dwarves[bs]);
    }
    
    int visited[dwarve_count];
    vector<int> stack;
    for (int i=0;i<dwarve_count;i++) {
        for (int j=0;j<dwarve_count;j++) {
            visited[j]=0;
        }
        stack.push_back(i);
        visited[i]=1;
        while (!stack.empty()) {
            int v=stack.back();
            stack.pop_back();
            for (int j=0;j<tallers[v].size();j++) {
                int w=tallers[v][j];
                if (w==i) {
                    cout << "impossible" << endl;
                    exit(0);
                }
                if (visited[w]==0) {
                    stack.push_back(w);
                    visited[w]=1;
                }
            }
        }
    }
    cout << "possible" << endl;
}
