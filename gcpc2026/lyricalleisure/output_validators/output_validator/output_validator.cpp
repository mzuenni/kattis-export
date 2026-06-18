#include "validation.h"

int manacher_len(std::string t) {
    std::string s;
    for (char c: t) s += std::string("#") + c;
    s += "#";
    int n = s.size();
    s = "$" + s + "^";

    std::vector<int> p(n + 2);
    int l = 0, r = 1;
    for (int i = 1; i <= n; i++) {
        if (i <= r) {
            p[i] = std::min(r - i, p[l + (r - i)]);
        }
        while (s[i - p[i]] == s[i + p[i]]) {
            p[i]++;
        }
        if (i + p[i] > r) {
            l = i - p[i];
            r = i + p[i];
        }
    }

    return *max_element(p.begin(), p.end()) - 1;
}

int main(int argc, char *argv[]) {
    std::ifstream in(argv[1]);
    OutputValidator v(argc, argv);

    int n, k;
    in >> n >> k;
    std::string answer = v.read_string("answer", n, n, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
    v.newline();
    std::transform(answer.begin(), answer.end(), answer.begin(), [](unsigned char c){ return std::tolower(c); });
    int ans = manacher_len(answer);
    v.check(ans == k, "Wrong length of longest palindromic substring (expected " + std::to_string(k) + ", got " + std::to_string(ans) + ").");
}
