fun main() {
    val n = readln().toInt()
    val p = readln().split(" ").map { it.toInt() }.sortedDescending()
    val sum = p.sum()
    val dp = LongArray(sum + 1)
    dp[0] = 1L
    var ans = 0L
    for (i in 0 until n) {
        for (j in sum downTo p[i]) {
            if (j > sum - j && (j - p[i]) <= sum - (j - p[i])) {
                ans += dp[j - p[i]]
            }
            dp[j] += dp[j - p[i]]
        }
    }
    println(ans)
}
