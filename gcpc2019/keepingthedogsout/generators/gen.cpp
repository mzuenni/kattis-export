#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

#include <cassert>

using namespace std;

typedef long long ll;


ll seed;
default_random_engine e;

// maximal sum of areas
ll max_area;

// n as described in the task statement.
// This is only an upper limit, the actual n may be smaller.
int largest_stone;

// whether the result should be possible or random
bool possible;

// Possible options:
//   hcn: the area is a highly composite number, i.e. there are many different rectangles of the correct size
//   prime: the area is the product of two primes
//   square
//   powerof2
//   random
string area_type;

// Probability to change large stones to smaller ones
double small_stone_probability;



constexpr pair<ll, ll> impossible = {-1, -1};

pair<ll, ll> solve(vector<ll> v)
{
    int n = v.size() - 1;
    ll a = 0;
    for (int i = 0; i <= n; i++) a += v[i] << (2*i);

    for (ll h = 1; h*h <= a; h++) {
        ll w = a/h;
        ll sum = 0;
        bool ok = true;
        for (int i = n; i >= 0; i--) {
            sum = 4*sum + v[i];
            if (sum > (h >> i) * (w >> i)) ok = false;
        }
        if (ok) return {h, w};
    }
    return impossible;
}


ll get_random(ll maximum)
{
    return uniform_int_distribution<ll>(0, maximum)(e);
}


ll get_highly_composite_number(ll maximum)
{
    // list of all highly composite numbers up to 10^18
    constexpr ll hcn[] = {1, 2, 4, 6, 12, 24, 36, 48, 60, 120, 180, 240, 360, 720, 840, 1260, 1680, 2520, 5040, 7560, 10080, 15120, 20160, 25200, 27720, 45360, 50400, 55440, 83160, 110880, 166320, 221760, 277200, 332640, 498960, 554400, 665280, 720720, 1081080, 1441440, 2162160, 2882880, 3603600, 4324320, 6486480, 7207200, 8648640, 10810800, 14414400, 17297280, 21621600, 32432400, 36756720, 43243200, 61261200, 73513440, 110270160, 122522400, 147026880, 183783600, 245044800, 294053760, 367567200, 551350800, 698377680, 735134400, 1102701600, 1396755360, 2095133040, 2205403200, 2327925600, 2793510720, 3491888400, 4655851200, 5587021440, 6983776800, 10475665200, 13967553600, 20951330400, 27935107200, 41902660800, 48886437600, 64250746560, 73329656400, 80313433200, 97772875200, 128501493120, 146659312800, 160626866400, 240940299600, 293318625600, 321253732800, 481880599200, 642507465600, 963761198400, 1124388064800, 1606268664000, 1686582097200, 1927522396800, 2248776129600, 3212537328000, 3373164194400, 4497552259200, 6746328388800, 8995104518400, 9316358251200, 13492656777600, 18632716502400, 26985313555200, 27949074753600, 32607253879200, 46581791256000, 48910880818800, 55898149507200, 65214507758400, 93163582512000, 97821761637600, 130429015516800, 195643523275200, 260858031033600, 288807105787200, 391287046550400, 577614211574400, 782574093100800, 866421317361600, 1010824870255200, 1444035528936000, 1516237305382800, 1732842634723200, 2021649740510400, 2888071057872000, 3032474610765600, 4043299481020800, 6064949221531200, 8086598962041600, 10108248702552000, 12129898443062400, 18194847664593600, 20216497405104000, 24259796886124800, 30324746107656000, 36389695329187200, 48519593772249600, 60649492215312000, 72779390658374400, 74801040398884800, 106858629141264000, 112201560598327200, 149602080797769600, 224403121196654400, 299204161595539200, 374005201994424000, 448806242393308800, 673209363589963200, 748010403988848000, 897612484786617600};

    return *(upper_bound(begin(hcn), end(hcn), maximum) - 1);
}


// returns one of the x largest primes up to maximum
ll get_prime(ll maximum, size_t x = 0)
{
    assert(maximum <= 100 * 1000 * 1000);

    static vector<ll> primes = {2, 3};
    for (ll i = primes.back() + 2; primes.back() < maximum ; i += 2) {
        bool is_prime = true;
        for (int j = 0; primes[j] * primes[j] <= i; ++j) {
            if (i % primes[j] == 0) {
                is_prime = false;
                break;
            }
        }
        if (is_prime) primes.push_back(i);
    }

    assert(primes.size() > x);
    return *(upper_bound(begin(primes), end(primes), maximum) - 1 - get_random(x));
}


vector<ll> get_blocks(ll x, ll y)
{
    vector<ll> result;
    ll cnt = 0;
    for (int i = largest_stone; i >= 0; --i) {
        ll t = (x >> i) * (y >> i);
        result.push_back(t - cnt * 4);
        cnt = t;
    }
    return result;
}


vector<ll> get_blocks(ll area)
{
    vector<ll> result;
    for (int i = largest_stone; i >= 0; --i) {
        ll t = area >> (2 * i);
        result.push_back(t);
        area %= 1ll << (2 * i);
    }
    return result;
}

ll get_area()
{
    if (area_type == "hcn") {
        return get_highly_composite_number(max_area);
    } else if (area_type == "prime") {
        ll t = static_cast<ll>(sqrt(sqrt(max_area)));
        ll a = get_prime(static_cast<ll>(sqrt(max_area)), t);
        ll b = get_prime(max_area / a, t);
        return a * b;
    } else if (area_type == "square") {
        ll m = sqrt(max_area);
        ll a = m - get_random(m / 10);
        return a * a;
    } else if (area_type == "powerof2") {
        return 1ll << (8 * sizeof(ll) - __builtin_clzll(max_area) - 1);
    } else {
        return max_area - get_random(max_area / 10);
    }
}

// splits each block in four with the probability small_stone_probability
void split_blocks(vector<ll>& v)
{
    for (size_t i = 0; i < v.size() - 1; ++i) {
        ll t = binomial_distribution<ll>(v[i], small_stone_probability)(e);
        v[i] -= t;
        v[i + 1] += 4 * t;
    }
}

void print(vector<ll> testcase)
{
    reverse(testcase.begin(), testcase.end());
    while (testcase.size() && testcase.back() == 0) testcase.pop_back();
    cout << testcase.size() - 1 << "\n";
    for (size_t i = 0; i < testcase.size() - 1; ++i) cout << testcase[i] << " ";
    cout << testcase.back() << endl;
}

vector<ll> make_possible_testcase()
{
    ll a = get_area();

    vector<ll> possible_x;
    for (ll i = 1; i * i <= a; ++i) if (a % i == 0) possible_x.push_back(i);
    ll x = possible_x[get_random(possible_x.size() - 1)];
    ll y = a / x;

    auto v = get_blocks(x, y);
    split_blocks(v);
    return v;
}


vector<ll> make_random_testcase()
{
    auto v = get_blocks(get_area());
    split_blocks(v);
    return v;
}


int main()
{
    cin >> seed;
    e.seed(seed);
    cin >> max_area >> largest_stone >> possible >> area_type >> small_stone_probability;
    if (possible) print(make_possible_testcase());
    else print(make_random_testcase());
}
