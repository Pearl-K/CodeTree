#include <iostream>
#include <algorithm>
using namespace std;

int n, k;
int ret = 1e6+1;
int arr[1000000];
int prsBits[1000001];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> k;
    for (int i=0; i<n; ++i) cin >> arr[i];
    prsBits[0] = 0;
    for (int i=1; i<=n; ++i) prsBits[i] = prsBits[i-1] + (arr[i-1]%2);

    int st = 0, ed = 0;
    while (st <= ed && ed < n){
        if(prsBits[ed] - prsBits[st] >= k){
            ret = min(ret, (ed-st));
            st++;
        }
        else ed++;
    }
    cout << ret << "\n";
    return 0;
}
