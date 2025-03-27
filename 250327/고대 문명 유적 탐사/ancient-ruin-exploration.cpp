#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 5;
const int S = 3;

int grid[N][N];
int tmp[N][N];
int K, M;
queue<int> leftPieces;

int dy[4] = {0, 1, 0, -1};
int dx[4] = {1, 0, -1, 0};

bool inRange(int y, int x) {
    return 0 <= y && y < N && 0 <= x && x < N;
}

void copyGrid(int dest[N][N], int src[N][N]) {
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            dest[i][j] = src[i][j];
}

void rotate(int src[N][N], int sy, int sx, int cnt, int dest[N][N]) {
    copyGrid(dest, src);
    while (cnt--) {
        int temp[S][S];
        for (int i = 0; i < S; ++i)
            for (int j = 0; j < S; ++j)
                temp[j][S - 1 - i] = dest[sy + i][sx + j];
        for (int i = 0; i < S; ++i)
            for (int j = 0; j < S; ++j)
                dest[sy + i][sx + j] = temp[i][j];
    }
}

int calculateScore(int board[N][N]) {
    bool visited[N][N] = {};
    int score = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (!visited[i][j]) {
                queue<pair<int, int>> q, trace;
                q.push({i, j});
                trace.push({i, j});
                visited[i][j] = true;
                int val = board[i][j];

                while (!q.empty()) {
                    auto [y, x] = q.front(); q.pop();
                    for (int d = 0; d < 4; ++d) {
                        int ny = y + dy[d], nx = x + dx[d];
                        if (inRange(ny, nx) && !visited[ny][nx] && board[ny][nx] == val) {
                            visited[ny][nx] = true;
                            q.push({ny, nx});
                            trace.push({ny, nx});
                        }
                    }
                }

                if (trace.size() >= 3) {
                    score += trace.size();
                    while (!trace.empty()) {
                        auto [y, x] = trace.front(); trace.pop();
                        board[y][x] = 0;
                    }
                }
            }
        }
    }
    return score;
}

void fillOnlyZeros(int board[N][N], queue<int>& pieces) {
    for (int j = 0; j < N; ++j) {
        for (int i = N - 1; i >= 0; --i) {
            if (board[i][j] == 0 && !pieces.empty()) {
                board[i][j] = pieces.front();
                pieces.pop();
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> K >> M;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            cin >> grid[i][j];

    for (int i = 0; i < M; ++i) {
        int val;
        cin >> val;
        leftPieces.push(val);
    }

    while (K--) {
        int maxScore = -1;
        int bestGrid[N][N];
        int bestRot = 4, bestY = 5, bestX = 5;

        for (int sy = 0; sy <= N - S; ++sy) {
            for (int sx = 0; sx <= N - S; ++sx) {
                for (int rot = 1; rot <= 3; ++rot) {
                    int rotated[N][N];
                    rotate(grid, sy, sx, rot, rotated);
                    int score = calculateScore(rotated);

                    if (score > maxScore ||
                       (score == maxScore && (rot < bestRot ||
                       (rot == bestRot && (sx < bestX || (sx == bestX && sy < bestY)))))) {
                        maxScore = score;
                        bestRot = rot;
                        bestY = sy;
                        bestX = sx;
                        copyGrid(bestGrid, rotated);
                    }
                }
            }
        }

        if (maxScore <= 0) break;
        copyGrid(grid, bestGrid);

        while (true) {
            fillOnlyZeros(grid, leftPieces);
            int newScore = calculateScore(grid);
            if (newScore == 0) break;
            maxScore += newScore;
        }

        cout << maxScore << " ";
    }
    return 0;
}
