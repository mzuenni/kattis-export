fun main() {
    println(if (List(readln().toInt()) { readln().split(" ").chunked(2) }.flatten().groupBy { it }.any { it.value.size % 2 == 1 }) "yes" else "no")
}

private fun readln() = readLine()!! // TODO Only to make this submission compatible with Kattis' Kotlin 1.3, remove when upgrading to 1.6 or higher
