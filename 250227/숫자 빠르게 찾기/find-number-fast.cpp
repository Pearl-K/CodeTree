#include <iostream>
#include <algorithm>
using namespace std;
int n, m;
int arr[100000];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> arr[i];
    for (int i = 0; i < m; i++) {
        int x;
        cin >> x;
        auto pos = lower_bound(arr, arr+n, x);
        if (pos == arr+n) cout << -1 << "\n";
        else if(x != *pos) cout << -1 << "\n";
        else cout << pos-arr+1 << "\n";
    }
    return 0;
}
