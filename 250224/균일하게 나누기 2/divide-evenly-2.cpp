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
    vector<int> tmp;
    tmp.push_back(q1);
    tmp.push_back(q2);
    tmp.push_back(q3);
    tmp.push_back(q4);
    sort(tmp.begin(), tmp.end());

    return tmp[3];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;

    memset(grid, 0, sizeof(grid));
    for (int i = 0; i < N; i++) {
        cin >> x[i] >> y[i];
        grid[x[i]][y[i]] = 1;
    }

    // 2차원 누적합 구해서
    // a, b 기준으로 이중 for문으로 해결
    for(int i=0; i<=MAX; ++i){
        preSum[i][0] = 0;
    }

    for(int j=0; j<=MAX; ++j){
        preSum[0][j] = 0;
    }

    for(int i=1; i<=MAX; ++i){
        for(int j=1; j<=MAX; ++j){
            preSum[i][j] = grid[i-1][j-1] 
                           + preSum[i-1][j] 
                           + preSum[i][j-1] 
                           - preSum[i-1][j-1];
        }
    }

    int total = N; //전체 점의 개수
    int ret = INF;

    // O(N^2) 으로 전체 돌면서 체크
    for(int i=0; i<=MAX; ++i){
        for(int j=0; j<=MAX; ++j){
            int lu = preSum[i][j];
            int ru = preSum[i][N] - lu;
            int ld = preSum[N][j];
            int rd = preSum[N][N] - ld - ru + lu;

            int tmpMax = findMax(lu, ru, ld, rd);
            ret = min(ret, tmpMax);
        }
    }
    cout << ret << "\n";
    return 0;
}
