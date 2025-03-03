#include <iostream>
#include <algorithm>
#include <climits>
#define MAX_N 10000
#define MAX_NUM 100000
using namespace std;

int n, m;
int arr[MAX_N];

bool IsPossible(int k) {
    int cnt = 0;
    for(int i = 0; i < n; i++) {
        cnt += arr[i] / k;
    }

    return cnt >= m;
}

int main() {
    cin >> n >> m;
    for(int i = 0; i < n; i++)
        cin >> arr[i];
    
    int left = 1;                         
    int right = MAX_NUM;                  
    int ans = 0; 
    
    while (left <= right) {
        int mid = (left + right) / 2;
        if(IsPossible(mid)) {
            left = mid + 1;
            ans = max(ans, mid); 
        }
        else                               
            right = mid - 1;
    }
    cout << ans;
    return 0;
}
