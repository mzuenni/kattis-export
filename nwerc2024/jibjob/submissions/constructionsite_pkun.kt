import kotlin.math.*

fun main() {
    val pt = List(readInt()) { readInts() }
    val ans = pt.map { (x1, y1, h) ->
        minOf(h, pt.filter { it[2] > h }.minOfOrNull { (x2, y2, h2) ->
            floor(hypot((x2 - x1).toDouble(), (y2 - y1).toDouble())).toInt()
        } ?: h)
    }
    println(ans.joinToString("\n"))
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }