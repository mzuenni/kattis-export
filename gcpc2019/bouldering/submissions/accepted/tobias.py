#!/usr/bin/env python3
# -*- coding: UTF-8 -*-

import sys
import heapq
import math
from typing import List


def distance(p1, p2):
    return math.sqrt((p1[0] - p2[0]) ** 2 + (p1[1] - p2[1]) ** 2)


if __name__ == "__main__":
    y_max, x_max, r, s = map(int, sys.stdin.readline().split())
    y_max, x_max = y_max - 1, x_max - 1
    s = min(s + 1, (y_max - 1) * (x_max + 1) * 9 + 19)

    graph: List[List[int]] = []
    points, ss = [], []
    for y in range(y_max + 1):
        for x, c in enumerate(sys.stdin.readline().rstrip()):
            if c == '.':
                continue
            si = int(c)
            graph.append([])
            points.append((x, y_max - y))
            ss.append(si)

    n = len(graph)
    for i in range(n):
        for j in range(i, n):
            if distance(points[i], points[j]) <= r:
                graph[i].append(j)
                graph[j].append(i)

    pq = []
    dists = [[math.inf] * s for _ in range(n)]

    points_y_max = -1
    fin_index = -1
    points_y_min = math.inf
    start_index = -1

    for i, point in enumerate(points):
        y = point[1]
        if y < points_y_min:
            points_y_min = y
            start_index = i
        if y > points_y_max:
            points_y_max = y
            fin_index = i

    if ss[start_index] < s:
        heapq.heappush(pq, (0, start_index, ss[start_index]))
        dists[start_index][ss[start_index]] = 0
        visited = [math.inf] * len(points)

    while pq:
        dist, node, stamina = heapq.heappop(pq)
        if node == fin_index:
            break
        if visited[node] <= stamina:
            continue
        visited[node] = stamina

        for out in graph[node]:
            new_stamina = stamina + ss[out]
            if new_stamina < s and new_stamina < visited[out]:
                new_dist = dist + distance(points[node], points[out])
                if new_dist < dists[out][new_stamina]:
                    dists[out][new_stamina] = new_dist
                    heapq.heappush(pq, (new_dist, out, new_stamina))

    min_dist = math.inf
    min_stam = math.inf
    for i in range(s):
        if dists[fin_index][i] < min_dist:
            min_dist = dists[fin_index][i]
            min_stam = i

    if math.isinf(min_stam):
        print("IMPOSSIBLE")
    else:
        print(min_dist)
