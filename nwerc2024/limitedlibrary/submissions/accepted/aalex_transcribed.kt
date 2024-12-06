fun main() {
    val (n, m, x, y) = readln().split(" ").map{ it.toInt() }
    val a = readln().split(" ").map { it.toInt() }.sorted()
    val b = readln().split(" ").map { it.toInt() }.sorted()

    var lo = -1
    var hi = n + 1
    while (hi - lo > 1) {
        val mid = (lo + hi) / 2

        var i = 0
        var j = 0
        var k = 0
        while (i < m) {
            while (j < n && (b[i] > a[j] || k >= (if (j < mid) y else x))) {
                ++j
                k = 0
            }
            if (j >= n) break
            ++k
            ++i
        }

        if (i == m) {
            lo = mid
        } else {
            hi = mid
        }
    }

    if (lo < 0) {
        println("impossible")
    } else {
        println(lo)
    }
}
