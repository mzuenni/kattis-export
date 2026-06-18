#include "validate.h"
using namespace OutputValidator;

Integer N, M, C;
std::vector<std::vector<Integer>> ADJ;

bool verify(std::vector<Integer>& bands) {
	std::vector<bool> selected(N+M);
	for (Integer b : bands) selected[b] = true;
	for (Integer fan = N; fan < N+M; fan++) {
		Integer c = 0;
		for (Integer b : ADJ[fan]) c += selected[b];
		selected[fan] = 2*c >= ADJ[fan].size();
	}
	for (Integer band : bands) {
		Integer c = 0;
		for (Integer f : ADJ[band]) c += selected[f];
		if (c < C) return false;
	}
	return true;
}

// same method to parse/verify team and jury input
std::string parseAndVerify(InputStream& in, std::string_view who, Verdict onError) {
	std::regex options = caseSensitive.regex("(im)?possible");
	std::string ans = in.string(options);
	in.newline();

	if (stringEqual(ans, "possible")) {
		Integer k = in.integer(1, N+1);
		in.newline();
		std::vector<Integer> bands = in.integers(k, 1, N+1);
		if (!areDistinct(bands)) juryOut << who << " solution is invalid! (contains duplicates)" << onError;
		for (Integer& x : bands) x--;
		in.newline();

		if (!verify(bands)) juryOut << who << " solution is invalid!" << onError;
	}
	in.eof();
	return ans;
}

int main(int argc, char **argv) {
	OutputValidator::init(argc, argv);

	N = testIn.integer();
	M = testIn.integer();
	C = testIn.integer();
	ADJ.assign(N+M, {});
	for (Integer i = 0; i < M; i++) {
		Integer k = testIn.integer();
		for (Integer j = 0; j < k; j++) {
			Integer band = testIn.integer();
			band--;
			ADJ[band].push_back(N + i);
			ADJ[N + i].push_back(band);
		}
	}

	std::string j = parseAndVerify(juryAns, "jury", FAIL);
	std::string t = parseAndVerify(teamAns, "team", WA);

	if (stringEqual(j, t)) {
		juryOut << "OK same answer" << AC;
	} else if (stringEqual(t, "possible")) {
		juryOut << "team found solution but jury not!" << FAIL;
	} else if (stringEqual(j, "possible")) {
		juryOut << "jury found solution but team not!" << WA;
	} else {
		juryOut << "how did this happen?!" << FAIL;
	}
	return AC;
}
