#include <iostream>

using namespace std;

int n, k;
int arr[11];
int ret = 0;

int main() {
    cin >> n >> k;

    for(int i=0; i<n; ++i) {
        cin >> arr[i];
    }

    int tmp = k;
    for(int i=n-1; i >=0; --i){
        if (tmp == 0) break;
        ret += (tmp/arr[i]);
        tmp %= arr[i];
    }

    cout << ret << "\n";
    return 0;
}
