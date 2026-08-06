// Problem B: BrainFuckVM
// Author: Christian Ledig
// Expected Result: Correct <--- nein :-)
// @EXPECTED_RESULTS@: WRONG-ANSWER

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <string.h>

using namespace std;

unsigned char mem[100100];
char code[5000];
char inp[5000];
int ind; 
int inp_ind;
int s_m, s_c, s_i;
int lbrackets[5000];
int rbrackets[5000];
int jump_cnt[5000];
int bra_ind;

void incr_ind()
{
  //cout << "incrementing index" << endl;
  ind++;
  if( ind >= s_m ) ind = 0;  
}

void decr_ind()
{
  //cout << "decrementing index" << endl;
  ind--;
  if( ind < 0 ) ind = s_m - 1;  
}

void incr()
{
 // cout << "incrementing entry" << endl;
  //if( mem[ind] == 255 ) mem[ind] = 0;
  //else mem[ind]++;  
  mem[ind]++;  
}

void decr()
{
 // cout << "decrementing entry" << endl;
  //if( mem[ind] == 0 ) mem[ind] = 255;
  //else mem[ind]--;  
  mem[ind]--;
}

void print_c()
{
 // cout << "printing entry" << endl;
  // cout << (int) mem[ind];
}

void read_c()
{
 // cout << "reading entry" << endl;
  if( inp_ind >= s_i ) mem[ind] = 255;
  else mem[ind] = inp[inp_ind++];
 // cout << (int) mem[ind];
}

void run()
{
  int cnt = 0;
  int i = 0;

  for( ; i < s_c; ++i )
  {
    if( code[i] == '-' ) decr();
    else if( code[i] == '+' ) incr();
    else if( code[i] == '<' ) decr_ind();
    else if( code[i] == '>' ) incr_ind();
    else if( code[i] == '.' ) print_c();
    else if( code[i] == ',' ) read_c();        
    else if( code[i] == '[' ) 
    {
      if( mem[ind] == 0 ) 
      {
	int lvl = 1;
	++i;
	while( lvl ) 
	{
	  if( code[i] == '[' ) lvl++;
	  if( code[i] == ']' ) lvl--;    
	  ++i;
	}
	--i;
      }
      else
      {
	bra_ind++;
	lbrackets[bra_ind] = i;	
	jump_cnt[bra_ind] = 0;
      }      
    }
    else if( code[i] == ']' ) 
    {
      if( mem[ind] != 0 ) 
      {
	rbrackets[bra_ind] = i;
	i = lbrackets[bra_ind];
	jump_cnt[bra_ind]++;
      }
      else
      {
	bra_ind--;
      }
    }
    cnt++;
    if( cnt > 50000000 ) break;
  }  
  if( cnt < 50000000 )
  {
    cout << "Terminates" << endl;
  }
  else
  {
    int max_ind = 0;
    int max_val = 0;
    for ( int k = 0; k < 5000; ++k )
    {
      if( jump_cnt[k] > max_val ) 
      {
	max_val = jump_cnt[k];
	max_ind = k;
      }
    }
    cout << "Loops " << lbrackets[max_ind] << " " << rbrackets[max_ind] << endl;
  }  
}

int main(void) {
  int T;
  cin >> T;

  while (T--) {
    cin >> s_m >> s_c >> s_i;
   
    ind = 0;   
    inp_ind = 0;
    bra_ind = 0;
    memset( mem, 0, sizeof(mem) );
    memset( code, 0, sizeof(code) );
    memset( inp, 0, sizeof(inp) );
    memset( lbrackets, 0, sizeof(lbrackets) );
    memset( rbrackets, 0, sizeof(rbrackets) );    
    memset( jump_cnt, 0, sizeof(jump_cnt) );    

    string str_code, str_inp;
    getline( cin, str_code );
    getline( cin, str_code );
    strcpy(code, str_code.c_str() );
    getline( cin, str_inp );
    strcpy(inp, str_inp.c_str() );
    run();
  }
  return 0;
}
