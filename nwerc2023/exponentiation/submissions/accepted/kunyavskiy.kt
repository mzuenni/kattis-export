import kotlin.math.sign

class Number(val values: List<Number>) : Comparable<Number> {
    var index: Int = -1
    override operator fun compareTo(other: Number) : Int {
        if (index != -1 && other.index != -1) return index.compareTo(other.index)
        for (i in 0 until minOf(values.size, other.values.size)) {
            val r = values[i].compareTo(other.values[i])
            if (r != 0) return r
        }
        return values.size.compareTo(other.values.size)
    }

    override fun toString(): String {
        if (values.isEmpty()) return "0"
        return values.joinToString("+") { "2023^{$it}" }
    }
}

fun main() {
    val allNumbers = mutableListOf(Number(emptyList()))
    val (n, q) = readInts()
    val a = Array(n) { allNumbers[0] }
    repeat(q) {
        val (ty, ii, jj) = readStrings()
        val i = ii.toInt() - 1
        val j = jj.toInt() - 1
        if (ty == "!") {
            val nw = Number((a[i].values + a[j]).sortedDescending())
            val position = allNumbers.binarySearch(nw)
            if (position > 0) {
                a[i] = allNumbers[position]
            } else {
                a[i] = nw
                allNumbers.add(position.inv(), a[i])
                for (index in allNumbers.indices) {
                    allNumbers[index].index = index
                }
            }
        } else {
            val cmp = a[i].compareTo(a[j]).sign
            println(when {
                cmp < 0 -> "<"
                cmp > 0 -> ">"
                else -> "="
            })
        }
    }
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }