#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 1e9;
const int MAX = 1000;  // 좌표의 최대값: 0 ~ 1000 (즉, grid 크기는 1001 x 1001)

int N;
int x[1000];
int y[1000];
int grid[1001][1001];
int preSum[1002][1002];

int findMax(int q1, int q2, int q3, int q4) {
    return max({q1, q2, q3, q4});
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;

    memset(grid, 0, sizeof(grid));
    for (int i = 0; i < N; i++) {
        cin >> x[i] >> y[i];
        // 만약 입력 좌표가 1~1000 범위라면 여기서 1을 빼서 0-index로 맞춰야 합니다.
        grid[x[i]][y[i]] = 1;
    }

    // 2차원 누적합(preSum) 계산
    // preSum[i][j] = sum of grid[0..i-1][0..j-1]
    for(int i = 0; i <= MAX; ++i){
        preSum[i][0] = 0;
    }
    for(int j = 0; j <= MAX; ++j){
        preSum[0][j] = 0;
    }
    for(int i = 1; i <= MAX; ++i){
        for(int j = 1; j <= MAX; ++j){
            preSum[i][j] = grid[i-1][j-1] 
                           + preSum[i-1][j] 
                           + preSum[i][j-1] 
                           - preSum[i-1][j-1];
        }
    }

    int total = preSum[MAX][MAX]; // 전체 점의 개수
    int ret = INF;

    // 모든 분할 후보 (i, j) (0 <= i,j <= MAX)
    for(int i = 0; i <= MAX; ++i){
        for(int j = 0; j <= MAX; ++j){
            int lu = preSum[i][j]; // 좌상: 0 <= x < i, 0 <= y < j
            int ru = preSum[i][MAX] - preSum[i][j]; // 우상: 0 <= x < i, j <= y < MAX
            int ld = preSum[MAX][j] - preSum[i][j]; // 좌하: i <= x < MAX, 0 <= y < j
            int rd = total - (lu + ru + ld); // 우하: 나머지

            int tmpMax = findMax(lu, ru, ld, rd);
            ret = min(ret, tmpMax);
        }
    }
    cout << ret << "\n";
    return 0;
}
