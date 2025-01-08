fun main() {
    readInt()
    val a = readInts()
    var ones = a.count { it == 1 }
    var twos = a.count { it == 2 }
    val large = a.filter { it > 2 }.sorted()
    if (ones == 1 && twos == 0) {
        if (large.isEmpty()) println(1) else
        if (large.size == 1) println("1+${large[0]}") else
        println("(1+${large[0]})*" + large.drop(1).joinToString("*"))
        return
    }
    var s12 = 0
    var s11 = 0
    var s111 = 0
    while (ones > 0) {
        when {
            ones == 2 && (s11 + twos == 1) -> {
                s11++
                ones = 0
            }
            twos > 0 -> {
                twos--
                s12++
                ones--
            }
            s11 > 0 -> {
                s11--
                s111++
                ones--
            }
            else -> {
                require(ones != 1)
                s11++
                ones -= 2
            }
        }
    }
    println(buildString {
        for (i in large) {
            append(i)
            append("*")
        }
        repeat(twos) { append("2*")}
        repeat(s11) { append("(1+1)*")}
        repeat(s12) { append("(1+2)*")}
        repeat(s111) { append("(1+1+1)*")}
        deleteAt(length - 1)
    })
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }

private fun readln() = readLine()!! // TODO Only to make this submission compatible with Kattis' Kotlin 1.3, remove when upgrading to 1.6 or higher
