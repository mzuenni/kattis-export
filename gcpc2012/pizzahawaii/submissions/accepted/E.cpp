// Problem E: Pizza Hawaii
// Author: Christian Ledig
// Expected Result: Correct
// @EXPECTED_RESULTS@: CORRECT

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <set>
#include <map>

using namespace std;

int main(void) 
{
  int T, P, I_d, I_e;
  cin >> T;

  unsigned long long p_e[30];
  unsigned long long p_d[30];
  unsigned long long tmp_ull;
  
  vector<string> str_e;
  vector<string> str_d;
  map< string,int > map_e; 
  map< string,int > map_d;
  
  while( T-- )
  {  
    str_e.clear();
    str_d.clear();
    map_e.clear();
    map_d.clear();
    memset( p_e, 0, sizeof(p_e) );
    memset( p_d, 0, sizeof(p_d) );
    string cur_str;
    int cur_pos;
    
    cin >> P;
    while( P-- )
    {
      cin >> cur_str;
      cin >> I_d;
      while( I_d-- )
      {
	cin >> cur_str;
	if( map_d.find(cur_str) != map_d.end() )
	{
	  cur_pos = map_d[cur_str];
	}
	else
	{
	  cur_pos = str_d.size();
	  str_d.push_back(cur_str);
	  map_d.insert(make_pair( cur_str, cur_pos ) );
	}
	tmp_ull = p_d[cur_pos];
	tmp_ull += (1 << P);
	p_d[cur_pos] = tmp_ull;
      }
      cin >> I_e;
      while( I_e-- )
      {
	cin >> cur_str;
	if( map_e.find(cur_str) != map_e.end() )
	{
	  cur_pos = map_e[cur_str];
	}
	else
	{
	  cur_pos = str_e.size();
	  str_e.push_back(cur_str);
	  map_e.insert(make_pair( cur_str, cur_pos ) );
	}
	tmp_ull = p_e[cur_pos];
	tmp_ull += (1 << P);
	p_e[cur_pos] = tmp_ull;
      }
    }
    sort(str_d.begin(), str_d.end() );
    sort(str_e.begin(), str_e.end() );
    for( vector<string>::iterator iter_d=str_d.begin(); iter_d != str_d.end(); ++iter_d ) 
    {
      for( vector<string>::iterator iter_e=str_e.begin(); iter_e != str_e.end(); ++iter_e ) 
      {
	int pos_d = map_d[*iter_d];
	int pos_e = map_e[*iter_e];
	if( p_d[pos_d] == p_e[pos_e] ) 
	{
	  cout << "(" << *iter_d << ", " << *iter_e << ")" << endl;
	}	
      }      
    }
    if( T > 0 )
    {
      cout << endl;
    }
  }
  return 0;  
}
