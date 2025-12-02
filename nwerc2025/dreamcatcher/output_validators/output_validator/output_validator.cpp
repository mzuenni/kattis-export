#include "validation.h"
#include <numeric>
using namespace std;

int main(int argc, char *argv[]) {
    std::ifstream in(argv[1]);
    std::ifstream ans(argv[2]);
    OutputValidator team(argc, argv);

    long long n; in >> n;
    long long k_jury; ans >> k_jury;
    if(k_jury > n/2) k_jury = n-k_jury;
    long long k_team = team.read_integer("k", 1, n-1);
    team.newline();
    if(k_team > n/2) k_team = n-k_team;

    if(k_team != k_jury) {
        // sanity check jury approach
        auto res_jury = n / gcd(n,k_jury) * sin(M_PI * k_jury / n);
        auto res_team = n / gcd(n,k_team) * sin(M_PI * k_team / n);
        assert(res_team <= res_jury);
    }
    team.check(k_jury == k_team, "Answer for ", n, " not optimal. Got ", k_team, " but better would be ", k_jury);
}
