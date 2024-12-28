fun pow(base: Int, exp: Long, mod: Int): Long {
    var ans: Long = 1
    var base: Long = base.toLong()
    var exp: Long = exp.toLong()
    while (exp > 0) {
        if ((exp and 1) == 1L) {
            ans = (ans * base) % mod
        }
        exp = exp shr 1
        base = (base * base) % mod
    }
    return ans
}

fun main() {
    val (n, k) = readln().split(" ").map { it.toLong() }
    val s = readln()
    println((0 until n).map { s[((it * pow(2, k, n.toInt())) % n).toInt()] }.joinToString(""))
}
