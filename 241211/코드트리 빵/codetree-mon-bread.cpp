#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_N = 16;
const int MAX_M = 31;
const int INF = 1e9;

int n, m;
vector<vector<int>> grid(MAX_N, vector<int>(MAX_N));
vector<pair<int, int>> stores(MAX_M);

int dx[4] = {-1, 0, 0, 1};
int dy[4] = {0, -1, 1, 0};

int bfs(int x, int y) {
    queue<pair<int, int>> q;
    q.push({x, y});
    vector<vector<int>> dist(n, vector<int>(n, 0));
    int minDist = INF;

    while (!q.empty()) {
        auto [cx, cy] = q.front();
        q.pop();

        for (int i = 0; i < 4; ++i) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];

            if (nx >= 0 && ny >= 0 && nx < n && ny < n && dist[nx][ny] == 0 && !(nx == x && ny == y)) {
                dist[nx][ny] = dist[cx][cy] + 1;

                if (grid[nx][ny] == 1 && minDist > dist[nx][ny]) {
                    minDist = dist[nx][ny];
                    grid[nx][ny] = 2;
                } else {
                    q.push({nx, ny});
                }
            }
        }
    }

    return minDist;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> grid[i][j];
        }
    }

    for (int i = 0; i < m; ++i) {
        cin >> stores[i].first >> stores[i].second;
        stores[i].first -= 1; // 0-based index로 변환
        stores[i].second -= 1; // 0-based index로 변환
    }

    int ret=0;
    for (int idx = 0; idx < m; ++idx) {
        int x = stores[idx].first;
        int y = stores[idx].second;
        ret = max(ret, bfs(x, y) + idx + 1);
    }

    cout << ret << "\n";
    return 0;
}