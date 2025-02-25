#include <iostream>

using namespace std;

int n, m;
int A[100000];
int B[100000];

bool isSubsequence(){
    int st = 0;
    for(int i=0; i<m; ++i){
        while(st<n && A[st] != B[i]) st++;
        if(st == n) return false;
        else st++;
    }
    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> A[i];
    for (int i = 0; i < m; i++) cin >> B[i];
    if(isSubsequence()) cout << "Yes" << "\n";
    else cout << "No" << "\n";
    return 0;
}
