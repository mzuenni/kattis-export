import java.io.PrintWriter
import java.util.PriorityQueue
import kotlin.math.pow
import kotlin.math.sqrt

fun main() {
    val (n, m, qs) = readInts()
    val points = List(n) { readInts() }
    val g = List(n) { mutableListOf<Pair<Int, Double>>() }
    repeat(m) {
        val (a, b) = readInts().map { it - 1 }
        val dist = points[a].zip(points[b]).sumOf { (a, b) -> (a - b).toLong() * (a - b).toLong() }.toDouble().pow(0.25)
        g[a].add(b to dist)
        g[b].add(a to dist)
    }
    val d = DoubleArray(n) { Double.POSITIVE_INFINITY }
    d[0] = 0.0
    val q = PriorityQueue(compareBy(Pair<Int, Double>::second))
    q.add(0 to 0.0)
    val used = BooleanArray(n)
    while (q.isNotEmpty()) {
        val (v, _) = q.poll()
        if (used[v]) continue
        used[v] = true
        for ((u, dd) in g[v]) {
            if (d[u] > d[v] + dd) {
                d[u] = d[v] + dd
                q.add(u to d[u])
            }
        }
    }
    PrintWriter(System.out.buffered()).use {
        with(it) {
            repeat(qs) {
                val (u, c) = readInts()
                val du = d[u - 1]
                val normalized = c / du
                if (normalized < 2)
                    println("impossible")
                else {
                    val best = normalized - sqrt(normalized * normalized - 4)
                    println(best * du)
                }
            }
        }
    }
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }