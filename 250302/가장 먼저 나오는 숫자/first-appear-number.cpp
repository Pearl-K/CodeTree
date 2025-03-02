#include <iostream>
#include <algorithm>
using namespace std;

int n, m;
int arr[100000];
int query[100000];

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    for (int i = 0; i < m; i++) {
        cin >> query[i];
        auto pos = lower_bound(arr, arr+n, query[i]);
        if(pos == arr+n || *pos != query[i]) cout << -1 << "\n";
        else cout << pos - arr + 1 << "\n";
    }
    return 0;
}
