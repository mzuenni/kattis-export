#include <bits/stdc++.h>
#include "validate.h"
using namespace std;
using ll = long long;
using vl = vector<ll>;
#define sz(c) ll((c).size())
#define FOR(i,a,b) for(ll i = (a); i < (b); i++)
#define FORD(i,a,b) for(ll i = ll(b) - 1; i >= (a); i--)

const ll MAX_BASE = (2LL << 60) + 1;

ll check_and_parse_author(const string& to_parse) {
  //first pass; check for invalid character
  if(sz(to_parse) == 0) wrong_answer("Submission provided empty string to parse.\n");
  if(to_parse[0] == '+' && sz(to_parse) == 1) wrong_answer("Answer is not a number.\n");
  if(to_parse[0] != '+' && (to_parse[0] < '0' || '9' < to_parse[0])) wrong_answer("Answer contains invalid character.\n");
  FOR(i,1,sz(to_parse)) if(to_parse[i] < '0' || '9' < to_parse[i]) wrong_answer("Answer contains invalid character.\n");

  //second pass; calculate answer base
  ll base = 0;
  if(to_parse[0] != '+') base = to_parse[0] - '0';
  FOR(i,1,sz(to_parse)) {
    // avoid overflow
    if(MAX_BASE / 10 < base) return MAX_BASE;
    base = base*10 + (to_parse[i] - '0');
  }
  return base;
}
void multiply(vl &a, vl &b, vl &res, ll base) {
  res.assign(sz(res), 0);
  FOR(i,0,sz(a)) {
    FOR(j,0,sz(b)) {
      res[i + j] += a[i] * b[j];
      res[i + j + 1] += res[i + j] / base;
      res[i + j] %= base;
    }
  }
  FOR(i,0,sz(res) - 1) {
    res[i + 1] += res[i] / base;
    res[i] %= base;
  }
}

ll compare(vl &a, vl &b) {
  if(sz(a) < sz(b)) {
    FOR(i,sz(a),sz(b)) if(b[i] != 0) return -1;
  }
  if(sz(a) > sz(b)) {
    FOR(i,sz(b), sz(a)) if(a[i] != 0) return 1;
  }
  FORD(i,0,min(sz(a),sz(b))) {
    if(a[i] - b[i] != 0) return a[i] - b[i];
  }
  return 0;
}

int main(int argc, char **argv) {
  init_io(argc,argv);

  string a_ans, j_ans;
  char foo;
  judge_ans >> j_ans;
  if(!( author_out >> a_ans)) wrong_answer("Less output than expected.\n");
  if(author_out >> foo) wrong_answer("More output than expected.\n");
  transform(a_ans.begin(), a_ans.end(), a_ans.begin(), ::tolower);
  //quick accept
  if(a_ans == j_ans) accept();
  if(a_ans == "impossible") wrong_answer("Submission claims impossible, judge has answer.\n");

  ll base = check_and_parse_author(a_ans);
  if(base < 2) wrong_answer("Invalid base.\n");
  bool differs = false;
  if(j_ans == "impossible") differs = true;

  ll tmp, maxdigit = 1;
  judge_in >> tmp;
  vl a(tmp);
  FORD(i, 0, tmp) {judge_in >> a[i]; maxdigit = max(maxdigit, a[i]);}
  judge_in >> tmp;
  vl b(tmp);
  FORD(i, 0, tmp){ judge_in >> b[i]; maxdigit = max(maxdigit, b[i]);}
  judge_in >> tmp;
  vl prod(tmp);
  FORD(i, 0, tmp){ judge_in >> prod[i]; maxdigit = max(maxdigit, prod[i]);}
  vl res(sz(a) + sz(b) + 1);
  if(base < maxdigit + 1) wrong_answer("Base not greater than all occuring digits.\n");
  multiply(a,b,res,base);
  ll cmp = compare(prod, res);
  if(cmp == 0) {
    if(differs)
      judge_error("Judge answer is 'impossible' but submission gave valid answer.\n");
    accept();
  }
  wrong_answer("Invalid base.\n");
}
