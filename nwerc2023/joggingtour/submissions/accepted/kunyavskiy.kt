import kotlin.math.abs
import kotlin.math.hypot

fun main() {
    val a = List(readInt()) { readInts() }
    val dirs = mutableListOf<List<Double>>().apply {
        for (i in a.indices) {
            for (j in a.indices) {
                if (i >= j) continue
                val x = a[i][0] - a[j][0]
                val y = a[i][1] - a[j][1]
                val d = hypot(x.toDouble(), y.toDouble())
                add(listOf(x / d, y / d))
            }
        }
    }.toList()
    println(dirs.minOf { (x, y) ->
        val na = a.map { (it[0] * x + it[1] * y) to (it[0] * y - it[1] * x) }
        val dp = Array(1 shl na.size) { DoubleArray(na.size) { Double.POSITIVE_INFINITY } }
        for (i in dp.indices) {
            if (i.countOneBits() == 1) {
                dp[i][i.countTrailingZeroBits()] = 0.0
                continue
            }
            for (j in dp[i].indices) {
                if ((i and (1 shl j)) == 0) continue
                for (k in dp[i].indices) {
                    dp[i][j] = minOf(dp[i][j], dp[i xor (1 shl j)][k] + abs(na[j].first - na[k].first) + abs(na[j].second - na[k].second))
                }
            }
        }
        dp.last().min()!!
    })
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }

private fun readln() = readLine()!! // TODO Only to make this submission compatible with Kattis' Kotlin 1.3, remove when upgrading to 1.6 or higher
