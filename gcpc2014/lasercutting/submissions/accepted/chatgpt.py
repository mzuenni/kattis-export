import sys


def segment_intersects(a, b, c, d):
    """
    All segments are axis-aligned.
    Returns whether the closed segments intersect.
    """
    ax, ay = a
    bx, by = b
    cx, cy = c
    dx, dy = d

    # Both vertical
    if ax == bx and cx == dx:
        if ax != cx:
            return False
        return max(min(ay, by), min(cy, dy)) <= min(max(ay, by), max(cy, dy))

    # Both horizontal
    if ay == by and cy == dy:
        if ay != cy:
            return False
        return max(min(ax, bx), min(cx, dx)) <= min(max(ax, bx), max(cx, dx))

    # Make (a,b) the vertical segment and (c,d) the horizontal segment
    if ax == bx:
        vx, vy1, vy2 = ax, min(ay, by), max(ay, by)
        hy, hx1, hx2 = cy, min(cx, dx), max(cx, dx)
    else:
        vx, vy1, vy2 = cx, min(cy, dy), max(cy, dy)
        hy, hx1, hx2 = ay, min(ax, bx), max(ax, bx)

    return hx1 <= vx <= hx2 and vy1 <= hy <= vy2


def intersection_is_only_point(a, b, c, d, point):
    """
    Checks whether the intersection of the two segments is exactly 'point'.
    This is used for adjacent polygon edges.
    """
    if not segment_intersects(a, b, c, d):
        return False

    px, py = point
    ax, ay = a
    bx, by = b
    cx, cy = c
    dx, dy = d

    # Both vertical
    if ax == bx and cx == dx:
        if ax != cx:
            return False

        lo = max(min(ay, by), min(cy, dy))
        hi = min(max(ay, by), max(cy, dy))
        return lo == hi == py and px == ax

    # Both horizontal
    if ay == by and cy == dy:
        if ay != cy:
            return False

        lo = max(min(ax, bx), min(cx, dx))
        hi = min(max(ax, bx), max(cx, dx))
        return lo == hi == px and py == ay

    # Perpendicular segments: their intersection is one point
    if ax == bx:
        ix, iy = ax, cy
    else:
        ix, iy = cx, ay

    return (ix, iy) == point


def polygon_edges(poly):
    return [
        (poly[i], poly[i + 1])
        for i in range(len(poly) - 1)
    ]


def valid_polygon(poly):
    # A polygon must be closed.
    if poly[0] != poly[-1]:
        return False

    edges = polygon_edges(poly)
    m = len(edges)

    for i in range(m):
        for j in range(i + 1, m):
            if not segment_intersects(*edges[i], *edges[j]):
                continue

            # Consecutive edges may meet at their shared endpoint.
            if j == i + 1:
                common = poly[i + 1]
                if intersection_is_only_point(
                    edges[i][0], edges[i][1],
                    edges[j][0], edges[j][1],
                    common
                ):
                    continue

            # First and last edges may meet at the closing point.
            if i == 0 and j == m - 1:
                common = poly[0]
                if intersection_is_only_point(
                    edges[i][0], edges[i][1],
                    edges[j][0], edges[j][1],
                    common
                ):
                    continue

            # Any other intersection is invalid.
            return False

    return True


def bounding_box(poly):
    xs = [p[0] for p in poly]
    ys = [p[1] for p in poly]
    return min(xs), max(xs), min(ys), max(ys)


def boxes_intersect(box1, box2):
    minx1, maxx1, miny1, maxy1 = box1
    minx2, maxx2, miny2, maxy2 = box2

    return not (
        maxx1 < minx2 or maxx2 < minx1 or
        maxy1 < miny2 or maxy2 < miny1
    )


def polygons_intersect(poly1, poly2):
    box1 = bounding_box(poly1)
    box2 = bounding_box(poly2)

    if not boxes_intersect(box1, box2):
        return False

    edges1 = polygon_edges(poly1)
    edges2 = polygon_edges(poly2)

    for a, b in edges1:
        for c, d in edges2:
            if segment_intersects(a, b, c, d):
                return True

    return False


def point_inside_polygon(point, poly):
    """
    Ray casting algorithm.
    Boundary cases do not occur here because boundary intersections
    have already been checked.
    """
    x, y = point
    inside = False

    for i in range(len(poly) - 1):
        x1, y1 = poly[i]
        x2, y2 = poly[i + 1]

        # Does the horizontal ray from point cross this edge?
        if (y1 > y) != (y2 > y):
            intersection_x = x1 + (y - y1) * (x2 - x1) / (y2 - y1)

            if x < intersection_x:
                inside = not inside

    return inside


def solve():
    data = list(map(int, sys.stdin.buffer.read().split()))
    pos = 0

    t = data[pos]
    pos += 1

    answers = []

    for _ in range(t):
        p = data[pos]
        pos += 1

        polygons = []
        invalid = False

        for _ in range(p):
            n = data[pos]
            pos += 1

            poly = []
            for _ in range(n):
                x = data[pos]
                y = data[pos + 1]
                pos += 2
                poly.append((x, y))

            polygons.append(poly)

            if not valid_polygon(poly):
                invalid = True

        if invalid:
            answers.append("INVALID POLYGON")
            continue

        # Check intersections between different polygon boundaries.
        intersecting = False

        for i in range(p):
            for j in range(i + 1, p):
                if polygons_intersect(polygons[i], polygons[j]):
                    intersecting = True
                    break
            if intersecting:
                break

        if intersecting:
            answers.append("INTERSECTING POLYGONS")
            continue

        # Check nesting depth.
        nesting_count = [0] * p

        for i in range(p):
            test_point = polygons[i][0]

            for j in range(p):
                if i != j and point_inside_polygon(test_point, polygons[j]):
                    nesting_count[i] += 1

        if any(count > 1 for count in nesting_count):
            answers.append("INVALID NESTING")
        else:
            answers.append("CORRECT")

    print("\n".join(answers))


solve()
