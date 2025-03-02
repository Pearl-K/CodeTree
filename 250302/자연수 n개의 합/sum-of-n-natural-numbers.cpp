#include <iostream>
using namespace std;
using ll = long long;
ll s;
ll binarySearch(ll s) {
    ll left = 1, right = 2e9, ans = 0; 
    while (left <= right) {
        ll mid = (left + right)/2;
        ll sum = mid * (mid + 1)/2;
        if (sum <= s) {
            ans = mid;
            left = mid+1;
        } else {
            right = mid-1; 
        }
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> s;
    cout << binarySearch(s) << "\n";
    return 0;
}
