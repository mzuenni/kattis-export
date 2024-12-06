// rewritten andreas.cpp solution

fun main() {
    val (n, m) = readInts()
    val a = readInts() + listOf(0, 1)
    val g = List(n + 2) { mutableListOf<Int>() }
    repeat(m) {
        val (u, v) = readInts().map { it - 1 }
        g[u].add(v)
        g[v].add(u)
    }
    for (i in 0 until n) {
        g[i].add(n)
        g[i].add(n + 1)
        g[n].add(i)
        g[n + 1].add(i)
    }

    val N = Array(2) { IntArray(n+2) }
    for (u in g.indices) {
        for (v in g[u]) {
            N[a[v]][u]++
        }
    }

    val d = Array(2) { IntArray(n+2) { Int.MAX_VALUE } }
    val q = mutableListOf<Triple<Int, Int, Int>>()
    repeat(2) {
        q.add(Triple(n, it, 1))
        q.add(Triple(n + 1, it, 1))
    }
    var index = 0
    while (index < q.size) {
        val (u, `val`, c) = q[index++]

        if (d[`val`][u] <= c) continue
        d[`val`][u] = c

        val nxt = if (a[u] == `val`) (1 - `val`) else a[u]
        for (v in g[u]) if (a[v] == nxt) {
            if (d[a[u]][v] == Int.MAX_VALUE && --N[a[u]][v] == 0) q.add(Triple(v, a[u], c + 1))
        }
    }

    val r = Array(2) { IntArray(2) { 0 } }
    for (i in g.indices) for (j in 0 until 2) {
        r[a[i]][j] = maxOf(r[a[i]][j], d[j][i])
    }
    val res = r.minOf { it.min() }
    println(res.takeIf { it != Int.MAX_VALUE } ?: "infinity")
}


private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }
