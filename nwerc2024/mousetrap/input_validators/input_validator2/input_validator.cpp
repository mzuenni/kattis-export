#include "validation.h"

const int32_t MAXN = 200'000;
const int64_t MAXX = 10'000'000ll;

struct Vector2D
{
    int64_t x, y;
};

int main(int argc, char *argv[])
{
    InputValidator v(argc, argv);

    int32_t N = v.read_integer("n", 3, MAXN);
    v.newline();

    std::vector<Vector2D> P(N);

    for (int i = 0; i < N; i++)
    {
        P[i].x = v.read_integer("x", -MAXX, MAXX);
        v.space();
        P[i].y = v.read_integer("y", -MAXX, MAXX);
        v.newline();
    }

    long long sum = 0;
    for (int i = 0; i < N; i++) {
        sum += (P[(i + 1) % N].x - P[i].x) * (P[(i + 1) % N].y + P[i].y);

        v.check((P[(i + 1) % N].x - P[i].x) * (P[(i + 2) % N].y - P[i].y) - (P[(i + 2) % N].x - P[i].x) * (P[(i + 1) % N].y - P[i].y) > 0, "not a convex set");
    }
    v.check(sum < 0, "polygon not sorted counterclockwise");

    return 0;
}
