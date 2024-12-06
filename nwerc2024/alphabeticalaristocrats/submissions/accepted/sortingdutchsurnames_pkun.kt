fun main() {
    println(List(readln().toInt()) { readln() }.sortedBy { it.dropWhile { !it.isUpperCase() } }.joinToString("\n"))
}