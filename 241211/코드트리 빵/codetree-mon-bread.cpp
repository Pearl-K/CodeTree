#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
using pii = pair<int, int>;

const int MAX_N = 16;
const int MAX_M = 31;
const int INF = 1e9;
const int dr[4] = {-1, 0, 0, 1};  // 상, 좌, 우, 하 순서
const int dc[4] = {0, -1, 1, 0};

int N, M;
int arriveCnt = 0;
int grid[MAX_N][MAX_N];
pii goals[MAX_M];
pii pos[MAX_M];
bool arrived[MAX_M];
int distFromGoal[MAX_N][MAX_N][MAX_M];  // 각 칸에서 목표 지점까지의 최단 거리 (각 목표마다 별도로 계산)

bool rangeCheck(int r, int c) {
    return (1 <= r && r <= N && 1 <= c && c <= N);
}

// BFS로 목표까지의 최단 거리 계산 (한 번만 계산)
void bfsForGoal(int goalIndex) {
    queue<pii> Q;
    int dist[MAX_N][MAX_N];
    fill(&dist[0][0], &dist[MAX_N-1][MAX_N], -1);

    int gr = goals[goalIndex].first, gc = goals[goalIndex].second;
    Q.push({gr, gc});
    dist[gr][gc] = 0;

    while (!Q.empty()) {
        auto [r, c] = Q.front();
        Q.pop();

        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (!rangeCheck(nr, nc) || dist[nr][nc] != -1 || grid[nr][nc] == -1) continue;

            dist[nr][nc] = dist[r][c] + 1;
            Q.push({nr, nc});
        }
    }

    // 각 칸에 대해 해당 목표까지의 최단 거리 기록
    for (int r = 1; r <= N; ++r) {
        for (int c = 1; c <= N; ++c) {
            distFromGoal[r][c][goalIndex] = dist[r][c];
        }
    }
}

// BaseCamp를 찾을 때는 목표 지점에서 가장 가까운 베이스캠프를 찾음
pii findBasecamp(int gr, int gc) {
    queue<pii> Q;
    int dist[MAX_N][MAX_N];
    fill(&dist[0][0], &dist[MAX_N-1][MAX_N], -1);

    Q.push({gr, gc});
    dist[gr][gc] = 0;
    pii bestBC = {INF, INF};
    int minDist = INF;

    while (!Q.empty()) {
        auto [r, c] = Q.front();
        Q.pop();

        for (int i = 0; i < 4; ++i) { // 역탐색이므로 순서 반대로
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (!rangeCheck(nr, nc) || dist[nr][nc] != -1) continue;

            dist[nr][nc] = dist[r][c] + 1;

            if (grid[nr][nc] == 1 && minDist >= dist[nr][nc]) {
                // 행, 열 기준으로 가장 작은 베이스캠프 선택
                if (bestBC.first == INF ||
                    nr < bestBC.first ||
                    (nr == bestBC.first && nc < bestBC.second)) {
                    minDist = dist[nr][nc];
                    bestBC = {nr, nc};
                }
            }
            Q.push({nr, nc});
        }
    }
    return bestBC;
}

//t초에 해당하는 turn 끝나고 grid에서 못가는 칸 배열 받아서 잠그기
void blockSpace(vector<pii> &spaces) {
    for (const auto& pos : spaces) {
        grid[pos.first][pos.second] = -1;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;

    for (int r = 1; r <= N; ++r) {
        for (int c = 1; c <= N; ++c) {
            cin >> grid[r][c];
        }
    }

    for (int i = 1; i <= M; ++i) {
        cin >> goals[i].first >> goals[i].second;
    }

    // 각 목표에 대해 BFS를 한 번씩만 수행하여 distFromGoal 배열을 채움
    for (int i = 1; i <= M; ++i) {
        bfsForGoal(i);
    }

    int t = 0;
    while (true) {
        ++t;
        vector<pii> blockList;

        // 이미 도착한 사람 제외하고 이동
        for (int i = 1; i < t && i <= M; ++i) {
            if (pos[i] == goals[i]) continue;

            int r = pos[i].first, c = pos[i].second;
            int gr = goals[i].first, gc = goals[i].second;

            // 최단 거리 찾기 (distFromGoal 배열에서 값 참조)
            int minDist = INF;
            pii nextPos = {-1, -1};

            for (int j = 0; j < 4; ++j) {
                int nr = r + dr[j];
                int nc = c + dc[j];

                if (!rangeCheck(nr, nc) || grid[nr][nc] == -1) continue;

                int dist = distFromGoal[nr][nc][i];  // BFS 결과 배열에서 최단 거리 가져옴
                if (dist < minDist || (dist == minDist && j < 2)) {
                    minDist = dist;
                    nextPos = {nr, nc};
                }
            }

            // 이동
            if (nextPos.first != -1) {
                pos[i] = nextPos;
            }

            // 목적지 도착 확인
            if (pos[i] == goals[i] && !arrived[i]) {
                arrived[i] = true;
                arriveCnt++;
                blockList.push_back(pos[i]);
            }
        }

        // t번째 사람 BaseCamp로 이동
        if (t <= M) {
            pos[t] = findBasecamp(goals[t].first, goals[t].second);
            blockList.push_back(pos[t]);
        }

        // 이동 불가능한 좌표 잠그기
        blockSpace(blockList);
        if (arriveCnt == M) break;
    }

    cout << t;
    return 0;
}
