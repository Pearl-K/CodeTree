#include <iostream>
#include <algorithm>
using namespace std;
using ll = long long;

int n, m;
int points[100000];
int st[100000], ed[100000];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> points[i];
    for (int i = 0; i < m; i++) cin >> st[i] >> ed[i];
    sort(points, points+n);

    // 각 m개의 선분 위에 몇 개의 점이 존재하는지?
    // start 점의 lower bound pos
    // end 점의 upper bound - 1 pos
    for (int i=0; i<m; ++i){
        auto left = lower_bound(points, points+n, st[i]);
        auto right = upper_bound(points, points+n, ed[i]);
        int range = right - left;
        cout << range << "\n";
    }
    return 0;
}
