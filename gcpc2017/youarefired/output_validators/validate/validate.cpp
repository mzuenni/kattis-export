#include <vector>
#include <utility>
#include <string>
#include <unordered_map>
#include "validate.h"
typedef long long ll;
using namespace std;

int main(int argc, char **argv) 
{
	init_io(argc,argv);
	string fstLineJudge;
	string fstLineAuthor;
	getline(judge_ans, fstLineJudge);
	getline(author_out, fstLineAuthor);
	if (fstLineJudge == "impossible") {
		if (fstLineAuthor == fstLineJudge) {
			accept();
		} else {
			wrong_answer("Expected impossible\n");
		}
	}

	int numFiredJudge = stoi(fstLineJudge);
	int numFiredAuthor;
	try
	{
		numFiredAuthor = stoi(fstLineAuthor);
	}
	catch(...)
	{
		wrong_answer("Expected an integer in first line!\n");
	}
	
	if (numFiredJudge != numFiredAuthor)
		wrong_answer("Author fired %d employees but should have fired %d emplyees!\n", numFiredAuthor, numFiredJudge);

	int n,k;
	ll d;
	judge_in >> n >> d >> k;
	unordered_map<string,ll> employees;
	for (int i = 0; i < n; ++i)
	{
		string s;
		ll c;
		judge_in >> s >> c;
		employees[s] = c;
	}
	ll collected = 0;
	for (int i = 0; i < numFiredAuthor; ++i)
	{
		string s;
		getline(author_out, s);
		size_t p = s.find(", YOU ARE FIRED!");
		if (p == string::npos)
			wrong_answer("Cannot find ', YOU ARE FIRED!' in output line!\n");
		string emp = s.substr(0, p);
		if (employees.find(emp) == employees.end())
			wrong_answer("Author specified non-existing employee %s!\n", emp.c_str());
		collected += employees[emp];
	}
	if (collected < d)
		wrong_answer("Author only saved %lld but should have saved at least %lld!\n", collected, d);	
	accept();
}

