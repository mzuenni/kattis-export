fun main() {
    if (readln() == "send") {
        val n = readln().toInt()
        val s = readln()
        for (i in 0 until 5) {
            println(s.map { (it.code shr i) % 2 }.joinToString("") + "0".repeat(i))
        }
    } else {
        val a = List(5) { readln() }.sortedBy { it.length }
        val n = a[0].length
        var v = Array<Int>(n) { 96 }
        for (i in 0 until 5) {
            for (j in 0 until n) {
                v[j] += a[i][j].digitToInt() shl i
            }
        }
        println(v.map { it.toChar() }.joinToString(""))
    }
}
