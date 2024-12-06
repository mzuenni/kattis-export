import java.util.ArrayDeque

private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }

fun main() {
    val (n, m) = readInts()
	var a: MutableList<Int> = readInts().toMutableList()
	a.add(0)
	a.add(1)
    val g = List(n+2) { mutableListOf<Int>() }
    repeat (m) {
        val (a, b) = readInts()
        g[a-1].add(b -1)
        g[b-1].add(a -1)
    }
	for (i in 0..n-1) {
		g[i].add(n)
		g[i].add(n+1)
		g[n].add(i)
		g[n+1].add(i)
	}

	val N = List(n) { IntArray(2) { 0 } }
	for (i in 0..n-1) {
		for (v in g[i]) {
			N[i][a[v]]++
		}
	}
	val d = List(n+2) { IntArray(2) { Int.MAX_VALUE } }
	val q = ArrayDeque<Triple<Int, Int, Int>>()
	for (i in 0..1) {
		q.add(Triple(n, i, 1))
		q.add(Triple(n+1, i, 1))
	}
	while (q.isNotEmpty()) {
		val (u, vl, c) = q.pop()
		if (d[u][vl] <= c) continue
		d[u][vl] = c

		val nxt = if (a[u] == vl) (vl+1)%2 else a[u]
		for (v in g[u]) {
			if (a[v] == nxt) {
				if (d[v][a[u]] == Int.MAX_VALUE && --N[v][a[u]] == 0) q.add(Triple(v, a[u], c+1))
			}
		}
	}

	val r = List(2) { IntArray(2) { 0 } }
	for (i in 0..n+1) {
		for (j in 0..1) {
			r[a[i]][j] = maxOf(r[a[i]][j], d[i][j])
		}
	}
	val res = minOf(r[0][0], r[0][1], r[1][0], r[1][1])
	if (res < Int.MAX_VALUE) {
		println(res)
	} else {
		println("infinity")
	}
	
}
