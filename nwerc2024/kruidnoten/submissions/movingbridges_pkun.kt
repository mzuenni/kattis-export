import java.util.PriorityQueue

fun main() {
    System.setIn(System.`in`.buffered())
    val (n, m, k) = readInts()
    val g = List(n) { mutableListOf<Pair<Int, Int>>() }
    repeat(m) {
        val (a, b, l) = readInts()
        g[a-1].add(b -1 to l)
        g[b-1].add(a -1 to l)
    }

    fun getDists(start: Int) : LongArray {
        val d = LongArray(n) { Long.MAX_VALUE }
        d[start] = 0
        val q = PriorityQueue<Pair<Int, Long>> { a, b -> a.second.compareTo(b.second) }
        q.add(start to 0L)
        while (q.isNotEmpty()) {
            val (v, dd) = q.poll()
            if (dd != d[v]) continue
            for ((u, l) in g[v]) {
                if (d[u] <= dd + l) continue
                d[u] = dd + l
                q.add(u to d[u])
            }
        }
        return d
    }

    val dists1 = getDists(0)
    val distsn = getDists(n - 1)

    val exps = List(k) {
        val v = readStrings()
        v[1].toDouble() to dists1[v[0].toInt()-1] + distsn[v[0].toInt()-1]
    }.sortedBy { it.second }
    if (exps.none { it.first == 1.0 }) return println("impossible")
    var curP = 1.0
    var ans = 0.0
    for ((p, d) in exps) {
        ans += p * curP * d
        curP *= (1.0 - p)
    }
    println(ans)
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }
