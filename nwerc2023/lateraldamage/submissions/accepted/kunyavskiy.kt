fun main() {
    val (n,  k) = readInts()
    val hit = mutableSetOf<Int>()
    val asked = mutableSetOf<Int>()
    fun query(i: Int, j: Int) : String {
        if (hit.contains(i * 1000 + j)) return "hit"
        if (!asked.add(i * 1000 + j)) return "miss"
        if (i !in 0 until n || j !in 0 until n) return "miss"
        println("${i+1} ${j+1}")
        System.out.flush()
        return readln().also {
            if (it == "hit") {
                hit.add(1000 * i + j)
            }
        }
    }
    var killed = 0
    val dirs = listOf(1 to 0, -1 to 0, 0 to 1, 0 to -1)
    for (i in 0 until n) {
        for (j in 0 until  n) {
            if (killed == k) return
            if ((i + j) % 5 == 0) {
                when (query(i, j)) {
                    "miss" -> {}
                    "sunk" -> {
                        killed++
                    }
                    "hit" -> dirs@for ((dx, dy) in dirs) {
                        for (d in 1..4) {
                            when (query(i + dx * d, j + dy * d)) {
                                "miss" -> break
                                "hit" -> {}
                                "sunk" -> {
                                    killed++
                                    break@dirs
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    require(killed == k)
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }

private fun readln() = readLine()!! // TODO Only to make this submission compatible with Kattis' Kotlin 1.3, remove when upgrading to 1.6 or higher
