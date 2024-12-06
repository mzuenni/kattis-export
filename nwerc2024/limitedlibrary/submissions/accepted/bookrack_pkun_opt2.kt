fun main() {
    System.setIn(System.`in`.buffered())
    val (n, m, x, y) = readInts(4)
    val a = readInts(n)
    a.sort()
    val b = readInts(m)
    b.sort()
    fun check(k: Int): Boolean {
        var pt = 0
        for (i in a.indices) {
            val limit = minOf(b.size, pt + if (i < k) y else x)
            while (pt < limit && b[pt] <= a[i]) {
                pt++
            }
        }
        return pt == b.size
    }
    if (!check(0)) return println("impossible")
    var lf = 0
    var rg = a.size + 1
    while (rg - lf > 1) {
        val mid = (lf + rg) / 2
        if (check(mid)) {
            lf = mid
        } else {
            rg = mid
        }
    }
    println(lf)
}

private fun readInts(n: Int) = IntArray(n).also {
    var ptr = 0
    var cur = 0
    for (c in readln()) {
        if (c == ' ') {
            it[ptr++] = cur
            cur = 0
        } else {
            cur = cur * 10 + c.digitToInt()
        }
    }
    it[ptr] = cur
}
