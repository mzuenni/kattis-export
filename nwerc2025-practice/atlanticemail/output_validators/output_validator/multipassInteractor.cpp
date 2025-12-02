#include "validate.h"
constexpr int MAXN = 1e4;
inline const std::regex operationRegex("send|receive", REGEX_OPTIONS);
inline const std::regex lowerRegex("[a-z]*", REGEX_OPTIONS);
inline const std::regex bitsRegex("[01]*", REGEX_OPTIONS);
const int MAXT = 6;
struct Adversary {

};


int main(int argc, char **argv) {
	OutputValidator::init(argc, argv);
	Multipass::init();
	using namespace OutputValidator;
	using namespace Multipass;


	int x = juryAns.integer();
	std::mt19937 rng(x+pass);
	std::string operation = testIn.string();
	std::vector<std::string> bs(5);
	if(operation=="send") {
		int n = testIn.integer();
		std::string s = testIn.string();
		for(int j=0;j<5;++j) {
			bs[j] = teamAns.string(bitsRegex,1,n+11);
			teamAns.newline();
		}
		nextstate << n << std::endl;
		nextstate << s << std::endl;
	} else {
		int n = prevstate.integer();
		std::string s = prevstate.string();
		teamAns.expectString(s);
		teamAns.newline();
		for(int j=0;j<5;++j) {
			bs[j] = testIn.string();
		}
		nextstate << n << std::endl;
		nextstate << s << std::endl;
	}
	if(pass==MAXT-1) {
		teamOut << "ok (did " << pass+1 << " passes)" << AC;


	} else {
		std::shuffle(begin(bs),end(bs),rng);
		nextpass << "receive" << std::endl;

		for(auto i : bs) {
			nextpass << i << std::endl;
		}

		NEXT();
	}
	
}
