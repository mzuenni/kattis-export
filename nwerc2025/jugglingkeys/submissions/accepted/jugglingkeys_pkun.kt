fun main() {
    val (n, k, q) = readInts()
    val trips = List(q) { readInts() }
    val events = buildList<Triple<Int, Int, Int>> {
        for ((index, it) in trips.withIndex()) {
            add(Triple(it[1], -1, index))
            add(Triple(it[2], 1, index))
        }
        sortBy { it.first }
    }
    val needsKey = IntArray(q)
    var cur = n
    for ((_, delta, index) in events) {
        if (cur == 0 && delta == 1) needsKey[index] = 1
        cur += delta
    }
    var keysUsed = 0
    for ((_, delta, index) in events) {
        if (needsKey[index] == 1) keysUsed -= delta
        if (keysUsed > k) return println("impossible")
    }
    println(needsKey.joinToString(""))
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }