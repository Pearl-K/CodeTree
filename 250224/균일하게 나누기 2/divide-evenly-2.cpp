#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 1e9;
const int MAX = 1000;

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
        grid[x[i]][y[i]] = 1;
    }

    // 2차원 누적합(preSum)
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

    int total = preSum[MAX][MAX];
    int ret = INF;

    for(int i = 0; i <= MAX; ++i){
        for(int j = 0; j <= MAX; ++j){
            int lu = preSum[i][j]; // 좌상
            int ru = preSum[i][MAX] - preSum[i][j]; // 우상
            int ld = preSum[MAX][j] - preSum[i][j]; // 좌하
            int rd = total - (lu + ru + ld); // 우하

            int tmpMax = findMax(lu, ru, ld, rd);
            ret = min(ret, tmpMax);
        }
    }
    cout << ret << "\n";
    return 0;
}

