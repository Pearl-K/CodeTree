#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;
const int MOD = 7;
int N;
int ret = 0;
int num[50000];
int prsMod[50000];
unordered_map<int, int> firstShow;

int main() {
    cin >> N;
    for (int i = 0; i < N; i++) cin >> num[i];
    prsMod[0] = num[0]%MOD;
    for(int i=1; i<N; ++i) prsMod[i] = (prsMod[i-1] + num[i])%MOD;

    firstShow[0] = -1;
    for(int i=0; i<N; ++i){
        int val = prsMod[i];
        if(!firstShow.count(val)) firstShow[val] = i;
        ret = max(ret, i-firstShow[val]);
    }
    cout << ret << "\n";
    return 0;
}
