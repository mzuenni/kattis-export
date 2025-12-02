fun cs(n: Int) : DoubleArray {
    val x = DoubleArray(n + 1)
    x[0] = 1.0
    repeat(n) {
        for (j in n downTo 1) {
            x[j] = (x[j] + x[j - 1]) / 2.0
        }
        x[0] /= 2.0
    }
    return x
}

fun main() {
    readInt()
    val x = readln()
    val a = intArrayOf(
        x.count { it == 'r' },
        x.count { it == 'g' },
        x.count { it == 'b' },
    )
    a.sort()
    val probs = cs(a[0])
    println(probs.withIndex().sumOf {(k, prob) ->
        prob * (a[0] * 1.5 + minOf(a[1] + k, a[2] + a[0] - k) * 3)
    })
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }