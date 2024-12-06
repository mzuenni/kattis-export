#include "validation.h"

const int32_t MAXN = 200'000;
const int64_t MAXX = 10'000'000ll;

int main(int argc, char *argv[])
{
    InputValidator v(argc, argv);

    int32_t N = v.read_integer("n", 3, MAXN);
    v.newline();

    std::vector<std::pair<int,int>> ps(N);

    for (int i = 0; i < N; i++)
    {
        ps[i].first = v.read_integer("x", -MAXX, MAXX);
        v.space();
        ps[i].second = v.read_integer("y", -MAXX, MAXX);
        v.newline();
    }

    { // check for duplicates
        std::set<std::pair<int,int>> S;
        for (const auto &it : ps)
        {
            v.check(S.find(it) == S.end(), "duplicates were found");
            S.insert(it);
        }
    }

    // Check that each 3 consecutive points make a left turn.
    ps.push_back(ps[0]);
    ps.push_back(ps[1]);

    long double total_angle = 0;

    for(int i = 0; i < N; ++i){
        int64_t x1 = ps[i+1].first - ps[i].first;
        int64_t y1 = ps[i+1].second - ps[i].second;
        int64_t x2 = ps[i+2].first - ps[i+1].first;
        int64_t y2 = ps[i+2].second - ps[i+1].second;
        int64_t cross = x1 * y2 - x2 * y1;
        v.check(cross > 0, "three consecutive points do not make a left turn");

        // compute the angle using the cosine rule.
        long double dot = x1 * x2 + y1 * y2;
        long double len1 = sqrtl(x1 * x1 + y1 * y1);
        long double len2 = sqrtl(x2 * x2 + y2 * y2);
        long double cos = dot / len1 / len2;
        long double angle = std::acos(cos);
        total_angle += angle;
    }

    // Check that the total turn is correct.
    long double expected_total = 2*M_PI;
    v.check(std::abs(total_angle - expected_total) < 1e-6, "total turn is not correct, expected ", expected_total, " got ", total_angle);

    return 0;
}
