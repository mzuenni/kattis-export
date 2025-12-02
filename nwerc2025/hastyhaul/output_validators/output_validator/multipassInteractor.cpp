#include "validate.h"
constexpr int MAX_TESTCASES = 1e4;

struct testcase {
	Integer h, w, k;
	std::vector<std::string> state;

	std::string asString() const {
		std::string res = "|";
		for (auto& l : state) {
			res += l + '|';
		}
		return res;
	}

	bool solveable() const {
		Integer n = w*h;
		// binom(n,k) == 1 <=> k is subset of n
		return (n | k) != n;
	}
};

struct Adversary {
	virtual void notifyTest(const testcase& test, Integer fromY, Integer fromX, Integer toY, Integer toX) = 0;
	virtual std::vector<testcase> generateTests() = 0;
};

struct AdversaryNormal : public Adversary {
	void notifyTest(const testcase& test, Integer fromY, Integer fromX, Integer toY, Integer toX) override {
	}
	std::vector<testcase> generateTests() override {
		return {};
	}
};

/*
killed heuristic: the contestant splits the positions into disjoint groups and only performs swaps inside groups
idea of the adversary: for each grid size and k independently:
- build a graph of positions which were swapped
- assume that the connected components of the graph are the groups
- knapsack dp to distribute k among the groups
*/
struct AdversaryGroups : public Adversary {
	std::map<std::tuple<int, int, int>, std::set<std::pair<int, int>>> swaps;
	void notifyTest(const testcase& test, Integer fromY, Integer fromX, Integer toY, Integer toX) override {
		Integer u = fromY * test.w + fromX;
		Integer v = toY * test.w + toX;
		if (u > v) std::swap(u, v);
		swaps[{test.w, test.h, test.k}].emplace(u, v);
	}
	std::vector<testcase> generateTests() override {
		std::vector<testcase> res;
		for (auto [typ, edges] : swaps) {
			auto [w, h, k] = typ;
			Integer n = w*h;
			std::vector<std::vector<Integer>> g(n);
			for (auto [u, v] : edges) {
				g[u].push_back(v);
				g[v].push_back(u);
			}
			// for groups of size 1, we might miss information. Maybe the group is actually larger...
			for (Integer ignore1 = 0; ignore1 < 2; ignore1++) {
				std::vector<bool> vis(n);
				std::vector<std::vector<Integer>> components;
				auto dfs = [&](auto&& self, Integer u) -> void {
					vis[u] = true;
					components.back().push_back(u);
					for (Integer v : g[u]) {
						if(!vis[v]) self(self, v);
					}
				};
				for (Integer u = 0; u < n; u++){
					if (!vis[u]) {
						components.push_back(std::vector<Integer>());
						dfs(dfs, u);
						if(ignore1 && components.back().size() == 1) components.pop_back();
					}
				}
				// try to generate different test cases (to make it less likely that we use an unfinished group)
				for(Integer iter = 0; iter < 20; iter++){
					Random::shuffle(components);
					std::vector<std::vector<bool>> dp(1+components.size(), std::vector<bool>(n+1));
					dp[0][0] = true;
					for (Integer i = 0; i < components.size(); i++) {
						Integer s = std::ssize(components[i]);
						dp[i+1] = dp[i];
						for (Integer j = 0; j <= n-s; j++){
							if (dp[i][j]) dp[i+1][j+s] = true;
						}
					}
					if (!dp[components.size()][k]) continue;
					testcase test;
					test.h = h;
					test.w = w;
                    test.k = k;
					test.state.assign(h, std::string(w, '.'));
					Integer cur = k;
					for (Integer i = std::ssize(components)-1; i >= 0; i--) {
						Integer s = std::ssize(components[i]);
						if (cur >= s && dp[i][cur-s]) {
							for (Integer x : components[i]) {
								test.state[x/w][x%w] = '#';
							}
							cur -= s;
						}
					}
					res.push_back(test);
				}
			}
		}
		return res;
	}
};

int main(int argc, char **argv) {
	OutputValidator::init(argc, argv);
	Multipass::init();
	using namespace OutputValidator;
	using namespace Multipass;

	std::map<std::string, std::string> known;

	if (pass >= 1) {
		Integer k = prevstate.integer();
		for (Integer i = 0; i < k; i++) {
			std::string a = prevstate.string();
			std::string b = prevstate.string();
			known[a] = b;
		}
	}
	
	std::unique_ptr<Adversary> adversary = nullptr;
	std::string adversaryName = juryAns.string();
	// adversary only runs in pass 0
	if (pass >= 1 || adversaryName == "normal") adversary = std::unique_ptr<Adversary>(new AdversaryNormal());
	else if (adversaryName == "groups") adversary = std::unique_ptr<Adversary>(new AdversaryGroups());
	else judgeAssert(false, "invalide adversary type: " + adversaryName);
	
	bool hasNextPass = (pass == 0) || (pass == 1 && adversaryName != "normal");

	Integer t = testIn.integer();

	std::vector<testcase> testcases(t);
	std::vector<testcase> swappedCases;
	for (auto& cur : testcases) {
		cur.h = testIn.integer();
		cur.w = testIn.integer();
        cur.k = testIn.integer();
		cur.state.resize(cur.h);
		Integer cnt = 0;
		for (auto& l : cur.state) {
			l = testIn.string();
			for (char c : l) cnt += c == '#';
		}
		judgeAssert(cnt == cur.k, "the testcase has k=" + std::to_string(cur.k) + ", but the actual number of '#' is " + std::to_string(cnt));
	}
	
	
	Integer it = 0;
	for (auto& cur : testcases) {
		it++;
		if (cur.solveable()) {
			Integer fromY = teamAns.integer(1, cur.h+1) - 1;
			teamAns.space();
			Integer fromX = teamAns.integer(1, cur.w+1) - 1;
			teamAns.newline();
			if (cur.state[fromY][fromX] == '.') {
				teamOut << "WA on testcase " << it << " pass " << pass << ": no piece at " << fromX+1 << " " << fromY+1 << WA;
			}
			Integer toY = teamAns.integer(1, cur.h+1) - 1;
			teamAns.space();
			Integer toX = teamAns.integer(1, cur.w+1) - 1;
			teamAns.newline();
			if (cur.state[toY][toX] != '.') {
				teamOut << "WA on testcase " << it << " pass " << pass << ": cannot move piece to " << toX+1 << " " << toY+1 << WA;
			}
			
			adversary->notifyTest(cur, fromY, fromX, toY, toX);

			auto prev = cur.asString();
			std::swap(cur.state[fromY][fromX], cur.state[toY][toX]); // Note that cur is modified here!
			auto next = cur.asString();
			
			for (Integer order = 0; order < 2; order++){
				auto iter = known.find(prev);
				if (iter == known.end()) {
					iter = known.emplace(prev, next).first;
				}
				if (iter->second != next) {
					teamOut << "WA strategy is inconsistent in testcase " << it << " pass " << pass << WA;
				}
				std::swap(prev, next);
			}

			swappedCases.push_back(cur); // Note that we want to add the modified version of cur!
		} else {
			teamAns.expectString("risky");
			teamAns.newline();
		}
	}
	teamAns.eof();

	if (hasNextPass) {
		std::vector<testcase> cases = adversary->generateTests();
		cases.insert(cases.end(), swappedCases.begin(), swappedCases.end());
		if (cases.size() > MAX_TESTCASES) cases.resize(MAX_TESTCASES);
		nextpass << cases.size() << std::endl;
		for (testcase tc : cases) {
			nextpass << tc.h << " " << tc.w << " " << tc.k << std::endl;
			for (auto& l : tc.state) {
				nextpass << l << std::endl;
			}
		}
	}

	if (swappedCases.empty()) {
		teamOut << "ok (all testcases were unsolveable)" << AC;
	} else if (hasNextPass) {
		teamOut << "ok (preparing nextpass)" << std::endl;
		nextstate << known.size() << std::endl;
		for (auto [a, b] : known) {
			nextstate << a << " " << b << std::endl;
		}
		NEXT();
	} else {
		teamOut << "ok (did " << pass+1 << " passes)" << AC;
	}
}
