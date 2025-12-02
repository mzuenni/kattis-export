fun main() {
    val n = readInt()
    val g = List(n) { mutableListOf<Pair<Int, Int>>() }
    repeat(n - 1) {
        val (a, b, w) = readInts()
        g[a - 1].add(b - 1 to w)
        g[b - 1].add(a - 1 to w)
    }
    val d = IntArray(n) { 0 }
    repeat(readInt()) {
        val (a, b) = readInts().map { it - 1 }
        d[a]++
        d[b]++
    }
    val p = IntArray(n)

    var ans = 0L
    fun dfs(v: Int): Boolean {
        var cv = d[v]
        for ((u, c) in g[v]) {
            if (u != p[v]) {
                p[u] = v
                if (dfs(u)) {
                    ans += c
                    cv++
                }
            }
        }
        return cv % 2 == 1
    }
    dfs(0)
    println(ans)
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }