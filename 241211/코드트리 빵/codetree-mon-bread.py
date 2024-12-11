from collections import deque

n, m = map(int, input().split())
grid = [list(map(int, input().split())) for _ in range(n)]
stores = [map(int, input().split()) for _ in range(m)]

dx = [-1, 0, 0, 1]
dy = [0, -1, 1, 0]

def bfs(x, y):
  Q = deque()
  Q.append((x, y))
  distance = [[0]*n for _ in range(n)]
  min_distance = n*n

  while Q:
    cx, cy = Q.popleft()
    for i in range(4):
      nx = cx + dx[i]
      ny = cy + dy[i]
      if 0 <= nx < n and 0 <= ny < n and distance[nx][ny] == 0 and (nx, ny) != (x, y):
        distance[nx][ny] = distance[cx][cy] + 1
        if grid[nx][ny] == 1 and min_distance > distance[nx][ny]:
          min_distance = distance[nx][ny]
          grid[nx][ny] = 2
        else:
          Q.append((nx, ny))
  return min_distance

res = 0
for idx, (x, y) in enumerate(stores, start=1):
  res = max(res, bfs(x-1, y-1) + idx)
print(res)