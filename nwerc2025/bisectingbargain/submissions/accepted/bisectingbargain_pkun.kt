fun main() {
    var n = readInt()
    val div = buildList {
        for (i in listOfNotNull(500.takeUnless { n / 200 % 2 == 1 }, 200, 100, 50, 20, 10, 5, 2, 1)) {
            while (n >= i) {
                add(i)
                n -= i
            }
        }
    }
    if (div.groupingBy { it }.eachCount().all { (_, count) -> count % 2 == 0 }) {
        println("splittable")
    } else {
        println(div.size)
        println(div.joinToString(" "))
    }
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }