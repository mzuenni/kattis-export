def doIt():
    n,m = map(int, raw_input().split())
    
    g = [dict() for _ in range(n)]
    dist = [[0.0 for _ in range(n)] for _ in range(n)]
    
    for _ in range(m):
        sp = raw_input().split()
        a,b = map(lambda x: int(x)-1, sp[0:2])
        c = float(sp[2])
        if b in g[a]:
            c = max(c, g[a][b])
        g[a][b] = c
        dist[a][b] = c
        
        
    for mid in range(n):
        for start in range(n):
            for end in range(n):
                    dist[start][end] = max(dist[start][mid] * dist[mid][end], dist[start][end])
                    if start == end and dist[start][end] > 1.0:
                        print("inadmissible")
                        return
    print("admissible")


doIt()
