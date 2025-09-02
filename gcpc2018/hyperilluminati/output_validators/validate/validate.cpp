#include <bits/stdc++.h>
#include "validate.h"
using namespace std;

long long parse_int(string s, long long max) {
  long long s_int = 0;
  for(size_t i = 0; i < s.size(); i++) {
    if(s[i] < '0' || '9' < s[i])
      return -1;

    s_int *= 10;
    s_int += (long long) (s[i] - '0');
    if(s_int > max) return -1;
  }
  return s_int;
}

int main(int argc, char **argv) {
	init_io(argc,argv);
	
  string exp_line;
  string auth_line;
  string exp_dim, exp_step, auth_dim, auth_step;
	
  getline(judge_ans, exp_line);
	
  if (!(getline(author_out, auth_line))) 
    wrong_answer("Wrong answer; not enough output.\n");


  char foo;
	if (author_out >> foo)
		wrong_answer("Wrong answer: received more than expected output.\n");

  // Quick accept
  if(auth_line == exp_line)
    accept();

  stringstream auth_ss(auth_line);
  stringstream exp_ss(exp_line);

  // Impossible case
  if(auth_line[0] == 'i') {
    exp_ss >> exp_line;
    auth_ss >> auth_line;

    if(auth_ss >> foo)
		  wrong_answer("Wrong answer: received more than expected output.\n");
    
    if(auth_line != exp_line)
      wrong_answer("");

    accept();
  }

  // Possible case
  exp_ss >> exp_dim >> exp_step;

  if(!(auth_ss >> auth_dim >> auth_step))
    wrong_answer("Wrong answer: received less than expected output.\n");
	if (auth_ss >> foo)
		wrong_answer("Wrong answer: received more than expected output.\n");
  
  // Quick accept
  if(exp_dim == auth_dim && exp_step == auth_step)
    accept();

  long long exp_step_int = parse_int(exp_step, 1000*1000*1000);
  long long auth_step_int = parse_int(auth_step, exp_step_int);
  if(exp_step_int != auth_step_int)
    wrong_answer("Wrong answer: Steps mismatch.\n");

  // Quick accept
  if(exp_dim == auth_dim)
    accept();
    
  // 1 Block
  if (exp_step_int == 1) {
    long long auth_dim_int = 0;
    for(size_t i = 0; i < auth_dim.size(); i++) {

      // Check if author dimension only consists of numerical characters
      if(auth_dim[i] < '0' || '9' < auth_dim[i])
        wrong_answer("Wrong answer: found character other than number in answer\n");

      if(auth_dim_int < 3) {
        auth_dim_int = auth_dim_int * 10 + ((long long) (auth_dim[i] - '0'));
      }
    }
    // If dimension is smaller than 3, not valid
    if(auth_dim_int < 3)
      wrong_answer("Wrong answer: Dimension smaller than 3\n");
      
    accept();
  }

  // Trailing zeroes on author's answer?
  long long exp_dim_int = parse_int(exp_dim, 1000);
  long long auth_dim_int = parse_int(auth_dim, exp_dim_int);
  if(auth_dim_int != exp_dim_int)
    wrong_answer("Wrong answer: Dimension mismatch.\n");
  
  accept();
}

