fun solve(s: String, k: Long): String = when {
    k == 0L -> s
    s.length % 2 == 0 -> solve(buildString {
        for (i in s.indices step 2) {
            append(s[i])
        }
    }, k - 1).let { it + it }
    else -> {
        val coef = 2.toBigInteger().modPow(k.toBigInteger(), s.length.toBigInteger()).intValueExact()
        buildString {
            for (i in s.indices) {
                append(s[(i.toLong() * coef % s.length).toInt()])
            }
        }
    }
}

fun main() {
    val (_, k) = readLongs()
    println(solve(readln(), k))
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }