val cnk = Array(65) {
    LongArray(65) { 0 }
}

fun Long.toId(total: Int, count: Int) : Long {
    val bit = 1L shl (total - 1)
    return when  {
        count == 0 -> 0
        count == total -> 0
        (this and bit) == 0L -> toId(total - 1, count)
        else -> cnk[total][count] - (this - bit).toId(total - 1, count - 1) - 1
    }
}

fun Long.fromId(total: Int, count: Int) : Long {
    if (count == 0) return 0
    if (count == total) return (1L shl total) - 1
    val bit = 1L shl (total - 1)
    return if (this < cnk[total - 1][count]) {
        fromId(total - 1, count)
    } else {
        (cnk[total][count] - this - 1).fromId(total - 1, count - 1) + bit
    }
}

private fun solve() {
    val (n, m, k) = readInts()
    val a = List(n) { readln() }

    val l = a.indices.sumOf { i ->
        a[i].indices.sumOf { j ->
            if (a[i][j] == '#') 1L shl (i * m + j) else 0L
        }
    }
    val count = l.countOneBits()
    val total = n * m
    if (cnk[total][count] % 2 == 1L) return println("risky")
    val id = l.toId(total, count)
    val otherId = id xor 1L
    val result = otherId.fromId(total, count)
    val from = (0 until total).single { (l and (1L shl it)) != 0L && (result and (1L shl it)) == 0L }
    val to = (0 until total).single { (l and (1L shl it)) == 0L && (result and (1L shl it)) != 0L }
    println("${from / m + 1} ${from % m + 1}")
    println("${to / m + 1} ${to % m + 1}")
}

fun main() {
    for (i in 0 .. 64) {
        cnk[i][0] = 1
        for (j in 1..i) {
            cnk[i][j] = cnk[i - 1][j] + cnk[i - 1][j - 1]
        }
    }
    if (false) {
        for (total in 0 until 10) {
            for (count in 1..total) {
                if (cnk[total][count] == 1L) continue
                for (i in 0 until cnk[total][count]) {
                    val cur = i.fromId(total, count)
                    val next = ((i + 1) % cnk[total][count]).fromId(total, count)
                    println("$total $count $i: $cur $next")
                    require((cur xor next).countOneBits() == 2) {
                        "Not close: ${total}, ${count}, $i: ${cur}, $next"
                    }
                }
            }
            for (mask in 0L until (1L shl total)) {
                val count = mask.countOneBits()
                require(mask.toId(total, count).fromId(total, count) == mask) {
                    "Not invertible ${total}, ${count}, $mask"
                }
            }
        }
    }
    repeat(readInt()) {
        solve()
    }
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }
