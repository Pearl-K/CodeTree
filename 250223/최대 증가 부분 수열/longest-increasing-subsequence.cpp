#include <iostream>
#include <algorithm>
using namespace std;

int N;
int M[1000];
int lis[1000];

int main() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> M[i];
    }
    fill(lis, lis + N, 1);

    for(int i=0; i<N; ++i){
        for(int j=0; j<i; ++j){
            if(M[i] > M[j]){
                lis[i] = max(lis[j]+1, lis[i]);
            }
        }
    }

    int ret = 0;
    for(int i=0; i<N; ++i){
        ret = max(ret, lis[i]);
    }
    cout << ret << "\n";
    return 0;
}
