fun main() {
    readInt()
    val d = readInts().sortedDescending()
    val required = d.sum() / 2 + 1
    val dp = LongArray(required)

    dp[0] = 1
    var ans = 0L
    for (i in d) {
        for (curs in maxOf(0, required - i) until required) {
            ans += dp[curs]
        }
        for (j in required - 1 downTo i) {
            dp[j] += dp[j - i]
        }
    }
    println(ans)
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }