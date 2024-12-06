
fun main() {
    System.setIn(System.`in`.buffered())
    val a = List(readInt()) { readStrings().map { it.toBigInteger() } }
    fun prod(i: Int, j: Int) = a[i][0] * a[j][1] - a[i][1] * a[j][0]
    val area = a.indices.sumOf { i -> prod(i, (i + 1) % a.size) }
    var ans = 0.toBigInteger()
    var sx = 0.toBigInteger()
    var sy = 0.toBigInteger()
    for (i in a.indices.reversed()) {
        sx += a[i][0]
        sy += a[i][1]
        ans += a[i][0] * sy - a[i][1] * sx
    }
    ans *= a.size.toBigInteger()
    for (i in a.indices) {
        ans += (a[i][0] * sy - a[i][1] * sx) * (2 * i).toBigInteger()
    }
    println(ans.toDouble() / area.toDouble())
}

private fun readInt() = readln().toInt()
private fun readStrings() = readln().split(" ")
