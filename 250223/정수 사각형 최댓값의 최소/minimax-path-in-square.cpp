#include <iostream>
using ll = long long;
using namespace std;
const int INF = 1e6+1;

int n;
int grid[100][100];
int dp[100][100];

bool checkRange(int r, int c){
    return (0 <= r && r < n && 0 <= c && c < n);
}

int fillDp(int r, int c){
    if (r == 0 && c == 0) return grid[r][c];
    if(!checkRange(r, c)) return INF;
    return dp[r][c] 
        = min(max(fillDp(r-1, c), grid[r][c]), max(fillDp(r, c-1), grid[r][c]));
}

int main() {
    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }

    dp[0][0] = grid[0][0];
    fillDp(n-1, n-1);
    cout << dp[n-1][n-1] << "\n";
    return 0;
}
