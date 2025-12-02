#include "validation.h"

int main(int argc, char* argv[]) {
	std::ifstream in(argv[1]);
	AnswerValidator v(argc, argv);

	int n;
	in >> n;
	std::set<std::string> answers;
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < 10; ++j) {
			std::string ans;
			in >> ans;
			answers.insert(ans);
		}
	}

	answers.insert("tie");

	std::string ans = v.read_string("answer", 1, 20);
	v.check(answers.contains(ans), "Answer ", ans, " not found in the input");
	v.newline();
}
