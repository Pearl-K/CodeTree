#include <iostream>

using namespace std;

int n;
int a[100000];
int tmp = 0;
int ret = -1e9;

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if(a[i] > ret) {
            ret = max(ret, a[i]);
        } 
        if(tmp + a[i] >= 0){
            tmp += a[i];
            ret = max(ret, tmp);
        }
        else tmp = 0;
    }
    cout << ret << "\n";
    return 0;
}
