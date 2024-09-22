fun main() {
    val data = List(7) { readln() }
    val (d, h) = readInts()
    val ans = (0 until (1 shl 7))
        .filter { it.countOneBits() == d }
        .maxOf { mask ->
            (0 until 24).map { h ->
                (0 until 7).count { d -> (mask and (1 shl d) != 0) && data[d][h] == '.' }
            }.sorted().takeLast(h).sum()
        }
    println("%.10f".format(ans.toDouble() / d/ h))
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }

private fun readln() = readLine()!! // TODO Only to make this submission compatible with Kattis' Kotlin 1.3, remove when upgrading to 1.6 or higher
