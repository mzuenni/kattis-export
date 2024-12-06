const val BLOCKED = '#'
const val UNSEEN = '.'
const val SEEN = ':'
const val CHECK = '!'

val DELTAS = arrayOf(
    Pair(-1, 0),
    Pair(0, -1),
    Pair(0, 1),
    Pair(1, 0),
)

class Solver(val h: Int,
             val w: Int,
             val status: Array<CharArray>,
             val puzzle: Array<IntArray>) {
  val dist2root = Array(h) { IntArray(w) }
  val backreach = Array(h) { IntArray(w) }
  val altStack = Array(h * w) { Pair(0, 0) }
  var stackLen = 0

  fun push(x: Int, y: Int, dist: Int) {
    status[x][y] = SEEN
    dist2root[x][y] = dist
    backreach[x][y] = dist
    altStack[stackLen++] = Pair(x, y)
  }

  fun isEven(a: Int, b: Int): Boolean {
    for (i in a..<b) {
      val (x, y) = altStack[i]
      status[x][y] = CHECK
    }

    var even = true
    for (i in a..<b) {
      var (x, y) = altStack[i]
      if (status[x][y] != CHECK) continue
      do {
        if (status[x][y] != CHECK) return false
        status[x][y] = SEEN
        even = !even
        val p = puzzle[x][y] - 1
        x = p / w
        y = p % w
      } while (Pair(x, y) != altStack[i])
      even = !even
    }
    return even
  }

  fun dfs(x: Int, y: Int, px: Int, py: Int): Boolean {
    for ((dx, dy) in DELTAS) {
      val x2 = x + dx
      val y2 = y + dy
      if (x2 < 0 || h <= x2) continue
      if (y2 < 0 || w <= y2) continue
      if (x2 == px && y2 == py) continue
      if (status[x2][y2] == BLOCKED) continue
      if (status[x2][y2] == SEEN) {
        backreach[x][y] = minOf(backreach[x][y], dist2root[x2][y2])
        continue
      }

      val pos = stackLen
      push(x2, y2, dist2root[x][y] + 1)
      if (!dfs(x2, y2, x, y)) return false
      if (backreach[x2][y2] >= dist2root[x][y]) {
        if (!isEven(pos, stackLen)) return false
        stackLen = pos
      }
      backreach[x][y] = minOf(backreach[x][y], backreach[x2][y2])
    }
    return true
  }

  fun isSolvable(): Boolean {
    push(h - 1, w - 1, 0)
    return dfs(h - 1, w - 1, -1, -1)
  }
}

fun main() {
  val (h, w) = readln().split(' ').map(String::toInt)
  val status = Array(h) { CharArray(w) }
  for (i in 0..<h) {
    status[i] = readln().toCharArray()
  }
  val puzzle = Array(h) { IntArray(w) }
  for (i in 0..<h) {
    puzzle[i] = readln().split(' ').map(String::toInt).toIntArray()
  }

  val b = Solver(h, w, status, puzzle).isSolvable()
  println(if (b) "possible" else "impossible")
}
