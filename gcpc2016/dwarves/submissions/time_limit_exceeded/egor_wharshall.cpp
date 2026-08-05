// calculates the transitive closure and than checks whether there are contradictions (connected[i,j]==true and connected[j,i]==true) 
// runs in O(n*n*n) and should tle

#include <bits/stdc++.h>
using namespace std;

const size_t max_n=10000;
bool connected[max_n][max_n]={false};

map<string,size_t> names;
size_t get_id(const string &name){
    auto it=names.find(name);
    if(it==names.end()){
        size_t id=names.size();
        names[name]=id;
        return id;
    }
    return it->second;
}	

bool has_contradictions(){
  	for(size_t i=0;i<max_n;i++)
	 for(size_t j=i+1;j<max_n;j++)
	   if(connected[i][j] and connected[j][i])
	        return true;
	        
    return false;
}

int main() {
    for (size_t i=0;i<max_n;i++)
        connected[i][i]=true;
    
    size_t m;
    cin>>m; 
	for(size_t i=0;i<m;i++) {
		string s, t, cmp;
		cin >> s >> cmp >> t;
		size_t first=get_id(s);
		size_t second=get_id(t);
		if (cmp == ">") swap(first,second);
		connected[first][second]=true;
	}
	
   //wharshall:
	for(size_t k=0;k<max_n;k++)
	 for(size_t i=0;i<max_n;i++)
	   if(connected[i][k])
	        for(size_t j=0;j<max_n;j++)
	            if(connected[k][j])
	                connected[i][j]=true;

	cout << (has_contradictions() ? "impossible" : "possible") << endl;
}

