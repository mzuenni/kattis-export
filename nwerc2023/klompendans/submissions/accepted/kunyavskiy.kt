fun moves(a: Int, b: Int) = buildList {
    for ((aa, bb) in listOf(a to b, b to a)) {
        add(aa to bb)
        add(-aa to bb)
        add(aa to -bb)
        add(-aa to -bb)
    }
}.distinct()

fun main() {
    val n = readInt()
    val (a, b) = readInts()
    val (c, d ) = readInts()
    val moves = listOf(moves(a, b), moves(c, d))
    val g = Array(2) { Array(n) { BooleanArray(n) } }
    val q = mutableListOf(Triple(0, 0, 0), Triple(0, 0, 1))
    var ptr = 0
    g[0][0][0] = true
    g[1][0][0] = true
    while (ptr < q.size) {
        val (x, y, ty) = q[ptr++]
        for ((dx, dy) in moves[ty]) {
            val nx = x + dx
            val ny = y + dy
            if (nx in 0 until n && ny in 0 until n && !g[1 - ty][nx][ny]) {
                g[1 - ty][nx][ny] = true
                q.add(Triple(nx, ny, 1 - ty))
            }
        }
    }
    println(q.distinctBy { it.first * n + it.second }.count())
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }