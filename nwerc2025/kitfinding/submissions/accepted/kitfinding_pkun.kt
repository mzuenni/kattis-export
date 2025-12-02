fun main() {
    val (h, w, k, i, t) = readInts()
    val s = "KIT" + "K".repeat(k-1) + "T".repeat(t-1) + "I".repeat(i-1)
    println(s.chunked(w).joinToString("\n"))
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }