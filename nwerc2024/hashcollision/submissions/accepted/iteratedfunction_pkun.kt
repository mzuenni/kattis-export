fun main() {
    val n = readInt()
    fun query(c: Int, r: Int) : Int {
        println("? $c $r")
        System.out.flush()
        return readInt()
    }
    val a = query(n, 1)
    val b = if (a == n) 1 else query(n - a, 1)
    println("! $a $b")
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }