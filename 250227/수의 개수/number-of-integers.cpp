#include <iostream>
#include <algorithm>
using namespace std;
int n, m;
int arr[100000];

int main() {
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    for (int i = 0; i < m; i++) {
        int x;
        cin >> x;
        auto li = lower_bound(arr, arr+n, x);
        auto ui = upper_bound(arr, arr+n, x);
        if(li == ui) cout << 0 <<"\n";
        else cout << ui-li <<"\n";
    }
    return 0;
}
