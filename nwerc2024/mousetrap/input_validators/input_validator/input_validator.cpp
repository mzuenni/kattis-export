#include "validation.h"

const int32_t MAXN = 200'000;
const int64_t MAXX = 10'000'000ll;

struct Vector2D
{
    int64_t x, y;

    Vector2D operator-(const Vector2D &other) const
    {
        return Vector2D{.x = x - other.x, .y = y - other.y};
    }

    int64_t operator^(const Vector2D &other) const
    {
        return x * other.y - y * other.x;
    }

    bool operator<(const Vector2D &other) const
    {
        if (x == other.x)
            return y < other.y;
        return x < other.x;
    }

    bool operator==(const Vector2D &other) const
    {
        return x == other.x && y == other.y;
    }
};

typedef std::vector<Vector2D> Polygon;

Polygon convexHull(std::vector<Vector2D> P)
{
    std::vector<Vector2D> upperHull, lowerHull;
    std::sort(P.begin(), P.end());

    for (const auto &a : P)
    {
        while (upperHull.size() >= 2)
        {
            auto N = upperHull.size();
            const auto &b = upperHull[N - 1], c = upperHull[N - 2];
            if (((a - b) ^ (c - b)) >= 0)
                upperHull.pop_back();
            else
                break;
        }
        upperHull.push_back(a);

        while (lowerHull.size() >= 2)
        {
            auto N = lowerHull.size();
            const auto &b = lowerHull[N - 1], c = lowerHull[N - 2];
            if (((a - b) ^ (c - b)) <= 0)
                lowerHull.pop_back();
            else
                break;
        }
        lowerHull.push_back(a);
    }

    auto &ret = upperHull;

    std::reverse(ret.begin(), ret.end());
    ret.insert(ret.end(), lowerHull.begin() + 1, lowerHull.end() - 1);

    return ret;
}

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

    { // check for duplicates
        std::set<Vector2D> S;
        for (const auto &it : P)
        {
            v.check(S.find(it) == S.end(), "duplicates were found");
            S.insert(it);
        }
    }

    auto Q = convexHull(P);

    { // check for convexity
        v.check(P.size() == Q.size(), "not a convex set, convex hull = ", Q.size());
    }

    { // check for counterclockwise order in a hacky way cuz i'm too lazy to google the proper way
        for (int i = 0; i < N; i++)
        {
            if (Q[i] == P[0])
            {
                for (int j = 0; j < N; j++)
                    v.check(Q[(i + j) % N] == P[j], "polygon not sorted counterclockwise");
                break;
            }
        }
    }

    return 0;
}
