import kotlin.math.*

fun main() {
    var a = List<Pair<Int,Int>>(5) {
        readln().split(" ").map { it.toInt() }.let { it[0] to it[1] }
    }

    var res = 0
    repeat(8) {
        if (a.size > 1) {
            val v = a.map { it.first }.sorted()
            if (v[0] < v[1]) {
                res += v[1]-v[0]
                a = a.map { (x, y) -> Pair(max(x, v[1]), y) }.distinct()
            }
        }
        a = a.map { (x, y) -> Pair(-y, x) }
    }

    val v = a.map { it.first }.sorted()
    val w = a.map { it.second }.sorted()
    val dx = v.last() - v[0]
    val dy = w.last() - w[0]
    res += 2 * (dx + dy)

    if (a.any { (x, y) -> x != v[0] && x != v.last() && y != w[0] && y != w.last() }) {
        res += min(dx, dy)
    }
    println(res)
}
