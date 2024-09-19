#include <bits/stdc++.h>
#include "validate.h"

#define DEBUG true

using namespace std;
using ll = long long;
using ull = unsigned long long;

// Parses a string into a pair of integers
// Returns {full Euro, Cent}
pair<ull,ull> safe_price_parse(const string& s_price, const bool is_author = true) {
	auto check_char = [&s_price, is_author](const char &c) {
		if(c < '0' || '9' < c) {
			if(is_author)
				wrong_answer("Wrong answer: Found non-digit character in price (%s).\n", s_price.data());
			judge_error("Judge error: Found non-digit character in price (%s).\n", s_price.data());
		}
	};

	const size_t p_len = s_price.length();
	if(p_len < 4 || s_price[p_len - 3] != '.') {
		if(is_author)
			wrong_answer("Wrong answer: Price is formatted incorrectly (%s).\n", s_price.data());
		judge_error("Judge error: Price is formatted incorrectly (%s).\n", s_price.data());
	}

	ull euro = 0, cent = 0;
	size_t i = (s_price[0] == '+');

	for(; i < p_len - 3; ++i) {
		const char &c = s_price[i];
		check_char(c);
		const ull ull_c = (ull) (c - '0');
		if((ULLONG_MAX - ull_c) / 10 < euro) {
			if(is_author)
				wrong_answer("Wrong answer: Price is higher than ULLONG_MAX (%s).\n", s_price.data());
			judge_error("Judge error: Price is higher than ULLONG_MAX (%s).\n", s_price.data());
		}
		euro = euro * 10 + ull_c;
	}

	for(i = p_len - 2; i < p_len; ++i) {
		const char &c = s_price[i];
		check_char(c);
		cent = cent * 10 + ((ull) c - '0');
	}

	return {euro, cent};
}


// Safely multiplies a price with a constant to get the turnover
pair<ull, ull> safe_price_mult(const pair<ull, ull> &p, const ull mult, const bool is_author = true) {
	// returns a * b + c
	auto safe_mult = [is_author](const ull a, const ull b, const ull c) -> ull {
		if((ULLONG_MAX - c) / b < a) {
			if(is_author)
				wrong_answer("Wrong answer: Calculating author turnover results in integer higher than ULLONG_MAX.\n");
			judge_error("Judger error: Calculating judge turnover results in integer higher than ULLONG_MAX.\n");
		}
		return a * b + c;
	};
	ull euro = p.first, cent = p.second;
	cent = safe_mult(cent, mult, 0);
	euro = safe_mult(euro, mult, cent / 100);
	cent %= 100;
	return {euro, cent};
}


int main(int argc, char **argv) {
	init_io(argc,argv);

	string j_price, j_turn, a_price, a_turn;
	char foo;

	judge_ans >> j_price;
	if(!(author_out >> a_price))
		wrong_answer("Wrong answer: Missing price.\n");

	transform(j_price.begin(), j_price.end(), j_price.begin(), ::tolower);
	transform(a_price.begin(), a_price.end(), a_price.begin(), ::tolower);

	if(a_price == "impossible") {
		if(j_price != a_price)
			wrong_answer("Wrong answer: Author claims impossible but solution exists.\n");

		if(author_out >> foo)
			wrong_answer("Wrong answer: Trailing output.\n");

		accept();
	}

	// Author claims possible price

	if(!(author_out >> a_turn))
		wrong_answer("Wrong answer: Missing turnover.\n");

	if(author_out >> foo)
		wrong_answer("Wrong answer: Trailing output.\n");


	if(j_price != "impossible") {
		judge_ans >> j_turn;

		// All strings match; quick accept
		if(!DEBUG && j_price == a_price && j_turn == a_turn)
			accept();
	}

	ull n;
	judge_in >> n;
	vector<pair<pair<ull, ull>, pair<ull, ull>>> orders(n);

	while(n--) {
		ull buy, sell;
		std::string price;
		judge_in >> price >> buy >> sell;
		orders[n] = {safe_price_parse(price, false), {buy, sell}};
	}

	sort(orders.begin(), orders.end());
	for(size_t i = 1; i < orders.size(); ++i) {
		orders[i].second.second += orders[i - 1].second.second;
	}
	for(size_t i = orders.size() - 1; i > 0;) {
		orders[--i].second.first += orders[i].second.first;
	}

	// Find number of buy and sell orders at provided price
	auto get_fulfilled_orders = [&orders](pair<ull, ull> &price) -> ull {
		auto insert = lower_bound(orders.begin(), orders.end(), make_pair(price, make_pair(0ULL,0ULL)));
		ull buy_ord = 0, sell_ord = 0;
		if(insert != orders.end() && insert->first == price) {
			tie(buy_ord, sell_ord) = insert->second;
		} else {
			if(insert != orders.end()) {
				// Not higher than all prices => Buyers for higher price are ok with this price
				buy_ord = insert->second.first;
			}
			if(insert != orders.begin()) {
				// Not lower than all prices => Sellers for lower price are ok with this price
				sell_ord = prev(insert)->second.second;
			}
		}
		return min(buy_ord, sell_ord);
	};
	
	pair<ull, ull> a_pr_prsd = safe_price_parse(a_price);

	ull full_ord = get_fulfilled_orders(a_pr_prsd);

	if(full_ord == 0)
		wrong_answer("Wrong answer: Author printed price and turnover but no sales happen at printed price.\n");

	// Check if turnover matches price times sales
	pair<ull, ull> a_trn_prsd = safe_price_parse(a_turn);
	pair<ull, ull> calc_turn = safe_price_mult(a_pr_prsd, full_ord);
	if(a_trn_prsd != calc_turn) {
		wrong_answer("Wrong answer: Author price / turnover mismatch (Only %llu fulfilled orders for a total turnover of %llu.%02llu instead of %llu.%02llu).\n", 
				full_ord, calc_turn.first, calc_turn.second, a_trn_prsd.first, a_trn_prsd.second);
	}

	if(j_price == "impossible")
		judge_error("Judge_error: Judge claims impossible, but sales can happen.\n");

	if(!DEBUG && j_turn == a_turn)
		accept();

	// Mismatch of judge and author turnover; either suboptimal price or judge error (or DEBUG mode)
	pair<ull, ull> j_trn_prsd = safe_price_parse(j_turn, false);

	// Sanity check
	if(DEBUG) {
		pair<ull, ull> j_pr_prsd = safe_price_parse(j_price, false);
		full_ord = get_fulfilled_orders(j_pr_prsd);

		if(full_ord == 0)
			judge_error("Judge error: Judge printed price and turnover but no sales happen at printed price.\n");

		calc_turn = safe_price_mult(j_pr_prsd, full_ord, false);

		if(j_trn_prsd != calc_turn) {
			judge_error("Judge error: Judge price / turnover mismatch (Only %llu fulfilled orders for a total turnover of %llu.%02llu instead of %llu.%02llu).\n", 
					full_ord, calc_turn.first, calc_turn.second, j_trn_prsd.first, j_trn_prsd.second);
		}
	}


	if(j_trn_prsd == a_trn_prsd)
		accept();

	if(j_trn_prsd > a_trn_prsd)
		wrong_answer("Wrong answer: Author printed suboptimal price.\n");

	judge_error("Judge error: Author found better price than judge.\n");
}

