#include "validation.h"

int main(int argc, char* argv[]) {
	std::ifstream in(argv[1]);
	AnswerValidator v(argc, argv);

	long long maxn = 100'000;
	long long maxw = 1'000'000;

	int n;
	in >> n;
	int answer = v.read_integer("answer", 0, (maxn - 1) * maxw);
	v.newline();
}
