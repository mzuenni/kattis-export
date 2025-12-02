fun main() {
    val data = List(readInt()) { readStrings() }
    fun List<String>.eachCount() = groupingBy { it }.eachCount()
    fun List<String>.chooseOnlyMax(cands: List<String>): List<String> {
        val counts = groupingBy { it }.eachCount()
        val maxValue = cands.maxOf { counts[it] ?: 0 }
        return cands.filter { (counts[it] ?: 0) == maxValue }
    }
    val byTotal = data.flatten().chooseOnlyMax(data.flatten().distinct())
    val result = (0 until 10).fold(byTotal) { acc, pos ->
        data.map { it[pos] }.chooseOnlyMax(acc)
    }.singleOrNull()
    println(result ?: "tie")
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }