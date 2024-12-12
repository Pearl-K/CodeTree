#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include <tuple>
#include <cmath>

using namespace std;

const int BASECAMP = 1;
const int dx[] = {-1, 0, 0, 1};
const int dy[] = {0, -1, 1, 0};

int N, M;
vector<vector<int>> map;
vector<pair<int, int>> baseCamps;
vector<pair<int, int>> convenienceStores;
vector<tuple<int, int, int, int, bool>> persons;
set<pair<int, int>> banLocations;

bool isAllReached() {
    for (auto& person : persons) {
        if (!get<4>(person)) {
            return false;
        }
    }
    return true;
}

pair<int, int> findNearestBaseCamp(int startX, int startY) {
    vector<vector<bool>> visited(N + 1, vector<bool>(N + 1, false));
    queue<tuple<int, int, int>> q;
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;

    q.emplace(startX, startY, 0);
    visited[startX][startY] = true;

    while (!q.empty()) {
        auto [x, y, dist] = q.front();
        q.pop();

        if (map[x][y] == BASECAMP) {
            pq.emplace(dist, x, y);
        }

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx >= 1 && nx <= N && ny >= 1 && ny <= N && !visited[nx][ny] && map[nx][ny] != -1 &&
                !banLocations.count({nx, ny})) {
                visited[nx][ny] = true;
                q.emplace(nx, ny, dist + 1);
            }
        }
    }

    if (pq.empty()) return {-1, -1};
    return {get<1>(pq.top()), get<2>(pq.top())};
}

int getNextDirection(int curX, int curY, int targetX, int targetY) {
    vector<vector<bool>> visited(N + 1, vector<bool>(N + 1, false));
    queue<tuple<int, int, int>> q;
    q.emplace(curX, curY, -1);
    visited[curX][curY] = true;

    while (!q.empty()) {
        auto [x, y, dir] = q.front();
        q.pop();

        if (x == targetX && y == targetY) return dir;

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx >= 1 && nx <= N && ny >= 1 && ny <= N && !visited[nx][ny] && !banLocations.count({nx, ny})) {
                visited[nx][ny] = true;
                q.emplace(nx, ny, dir == -1 ? i : dir);
            }
        }
    }
    return -1;
}

void movePerson(int& curX, int& curY, int targetX, int targetY) {
    int dir = getNextDirection(curX, curY, targetX, targetY);
    if (dir != -1) {
        curX += dx[dir];
        curY += dy[dir];
    }
}

int main() {
    cin >> N >> M;
    map.assign(N + 1, vector<int>(N + 1));

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            cin >> map[i][j];
            if (map[i][j] == BASECAMP) {
                baseCamps.emplace_back(i, j);
            }
        }
    }

    for (int i = 0; i < M; ++i) {
        int x, y;
        cin >> x >> y;
        convenienceStores.emplace_back(x, y);
        persons.emplace_back(0, 0, x, y, false);
    }

    int time = 1;
    while (!isAllReached()) {
        // Move persons
        for (int i = 0; i < M; ++i) {
            auto& [curX, curY, targetX, targetY, isArrived] = persons[i];
            if (time > i + 1 && !isArrived) {
                movePerson(curX, curY, targetX, targetY);
            }
        }

        // Check if anyone arrived
        for (int i = 0; i < M; ++i) {
            auto& [curX, curY, targetX, targetY, isArrived] = persons[i];
            if (curX == targetX && curY == targetY) {
                isArrived = true;
                banLocations.insert({curX, curY});
            }
        }

        // Assign base camps
        for (int i = 0; i < M; ++i) {
            auto& [curX, curY, targetX, targetY, isArrived] = persons[i];
            if (time == i + 1) {
                auto [bx, by] = findNearestBaseCamp(targetX, targetY);
                curX = bx;
                curY = by;
                banLocations.insert({bx, by});
            }
        }

        ++time;
    }

    cout << time-1;
    return 0;
}
