fun main() {
    var (n, k) = readln().split(" ").map { it.toLong() }
    val s = readln()

    var offset: Long = 1
    var base: Long = 2
    while (k > 0) {
        if ((k and 1) == 1L) {
            offset = (offset * base) % n
        }
        k = k shr 1
        base = (base * base) % n
    }

    println((0 until n).map { s[((it * offset) % n).toInt()] }.joinToString(""))
}
