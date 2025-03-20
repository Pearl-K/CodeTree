import sys
input = sys.stdin.readline
n, m = map(int, input().split())
edges = [tuple(map(int, input().split())) for _ in range(m)]
INF = sys.maxsize

# Please write your code here.
dist = [[INF]*(n+1) for _ in range(n+1)]

for u, v, w in edges:
    dist[u][v] = min(dist[u][v], w)

for i in range(n+1):
    dist[i][i] = 0

for r in range(n+1):
    for p in range(n+1):
        for q in range(n+1):
            if dist[p][q] > dist[p][r] + dist[r][q]:
                dist[p][q] = dist[p][r] + dist[r][q]

for i in range(1, n+1):
    for j in range(1, n+1):
        print(dist[i][j] if dist[i][j] < INF else -1, end=" ")
    print()