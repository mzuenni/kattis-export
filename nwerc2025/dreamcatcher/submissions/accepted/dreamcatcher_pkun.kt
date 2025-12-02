tailrec fun gcd(a: Int, b: Int): Int = if (b == 0) a else gcd(b, a % b)

fun main() {
    val n = readInt()
    println(when (n % 4) {
        1, 3 -> n / 2
        2 -> n / 2 - 2
        else -> n / 2 - 1
    })
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }