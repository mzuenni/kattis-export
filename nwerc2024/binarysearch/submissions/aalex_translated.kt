import java.io.BufferedReader
import java.io.InputStreamReader
import java.util.*
import kotlin.math.max
import kotlin.math.min

internal class aalex(val labels: IntArray, val adjnodes: List<MutableList<Int>>) {
    val heights: IntArray = IntArray(2 * labels.size) // =0: unseen, <0: in progress, >0: done

    fun dfs(node: Int): Boolean {
        heights[node] = -1
        var h = 1
        for (i in adjnodes[node shr 1]) {
            if ((node and 1) == 0 && labels[i] != labels[node shr 1]) continue
            if ((node and 1) != 0 && labels[i] == labels[node shr 1]) continue
            val node2 = (i shl 1) xor (node and 1) xor 1
            if (heights[node2] < 0) return true
            if (heights[node2] == 0 && dfs(node2)) return true
            h = max(h.toDouble(), (heights[node2] + 1).toDouble()).toInt()
        }
        heights[node] = h
        return false
    }

    val length: Int
        get() {
            for (i in 0 until 2 * labels.size) {
                if (heights[i] > 0) continue
                if (dfs(i)) return -1
            }

            val lens = Array(2) { IntArray(2) }
            for (i in 0 until 2 * labels.size) {
                val a = i and 1
                val b = labels[i shr 1] and 1
                lens[a][b] = max(lens[a][b].toDouble(), heights[i].toDouble()).toInt()
            }

            return (1 + min(
                min(lens[0][0].toDouble(), lens[0][1].toDouble()),
                min(lens[1][0].toDouble(), lens[1][1].toDouble())
            )).toInt()
        }
}

fun main(args: Array<String>) {
    val reader =
        BufferedReader(InputStreamReader(System.`in`))

    val nm = reader.readLine().split(" ").toTypedArray()
    val n = nm[0].toInt()
    val m = nm[1].toInt()

    val labels =
        Arrays.stream(reader.readLine().split(" ").toTypedArray())
            .mapToInt { s: String -> s.toInt() }
            .toArray()

    val adjnodes: MutableList<MutableList<Int>> = ArrayList(n)
    for (i in 0 until n) adjnodes.add(ArrayList())
    for (i in 0 until m) {
        val uv = reader.readLine().split(" ").toTypedArray()
        var u = uv[0].toInt()
        var v = uv[1].toInt()
        --u
        --v
        adjnodes[u].add(v)
        adjnodes[v].add(u)
    }

    val len = (aalex(labels, adjnodes)).length
    if (len < 0) {
        println("infinity")
    } else {
        println(len)
    }
}

