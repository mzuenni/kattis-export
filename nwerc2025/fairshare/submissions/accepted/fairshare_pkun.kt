fun main() {
    val n = readInt()
    val d = List(n) { readLongs() }
    val price = d.sumOf { it[0] }
    val totalPaid = d.sumOf { it[1] }
    val res = d.indexOfFirst { it[0] <= price - (totalPaid - it[1]) }
    if (res == -1) println("impossible") else println(res + 1)
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }