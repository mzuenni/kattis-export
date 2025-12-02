fun main() {
    val n = readInt()
    var data = readInts().map { it - 1 }.toIntArray()
    val answer = mutableListOf<Pair<Int, Int>>()
    fun process(from: Int, to: Int) {
        require(from in 0..n -3)
        require(to in 0..n -3)
        require(from != to)
        answer.add(from to to)
        val new = IntArray(n)
        var pt = 0
        for (i in 0 until n) {
            if (i in to ..< to+3) {
                new[i] = data[from + i - to]
            } else {
                while (pt in from ..< from+3) pt++
                new[i] = data[pt++]
            }
        }
        data = new
    }

    fun swapPreLast() {
        process(n - 3, n - 5)
        process(n - 3, n - 4)
        process(n - 3, n - 5)
    }
    fun swapLast() {
        process(n - 3, n - 4)
        swapPreLast()
        process(n - 4, n - 3)
    }

    for (i in 0 ..< n - 3) {
        while (true) {
            val curIndex = data.indexOf(i)
            if (curIndex == i) break
            process(minOf(curIndex, n - 3), i)
        }
    }
    if (data[n - 3] > data[n - 2]) swapPreLast()
    if (data[n - 2] > data[n - 1]) swapLast()
    if (data[n - 3] > data[n - 2]) swapPreLast()

    println(answer.size)
    println(answer.joinToString("\n") { "${it.first + 1} ${it.second + 1}" })
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }