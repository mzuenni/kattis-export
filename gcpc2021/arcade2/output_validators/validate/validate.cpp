#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include "validate.h"
using namespace std;

using ll = long long;

int main(int argc, char **argv) 
{
	init_io(argc,argv);
	string judegeResStr; judge_ans >> judegeResStr;
	if (judegeResStr == "impossible") 
	{
		string teamResStr; 
		author_out >> teamResStr;
		if (teamResStr != "impossible")
		{
			wrong_answer("WA: supposed to be impossible, team says otherwise");
		}
	}
	else
	{
		// parse teamRes to integer
		ll teamRes; 
		author_out >> teamRes;
		if(author_out.fail())
		{
			wrong_answer("WA: team did not output an integer");
		}
		// read input
		ll n; judge_in >> n;
		// host's arcade label too small
		if (teamRes < 1)
		{
			wrong_answer("WA: host sits at an arcade with label < 1");
		}
		// host's arcade label too large
		if (teamRes > n)
		{
			wrong_answer("WA: host sits at an arcade with label > n");
		}
		// host's arcade label is even
		if (teamRes % 2 == 0)
		{
			wrong_answer("WA: host sits at an arcade labeled with an even number");
		}
		ll left = teamRes;
		ll right = n - teamRes + 1;
		// wrong size left interval
		if (((left-1) & (left-2)) != 0)
		{
			wrong_answer("WA: not all guests will get a seat");
		}
		// wront size right interval
		if (((right-1) & (right-2)) != 0)
		{
			wrong_answer("WA: not all guests will get a seat");
		}
	}
	// check for trailing output
	string trailing;
	if(author_out >> trailing)
	{
		wrong_answer("WA: trailing output");
	}
	accept();
}
