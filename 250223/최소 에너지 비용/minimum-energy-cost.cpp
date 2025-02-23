#include <iostream>
using namespace std;
using ll = long long;

int n;
int dist[100000];
int cost[100000];

int main() {
    cin >> n;
    for (int i = 0; i < n - 1; i++) cin >> dist[i];
    for (int i = 0; i < n; i++) cin >> cost[i];
    ll minCost = cost[0];
    ll res = 0;

    for(int i =0; i < n-1; i++){
        if(cost[i] < minCost){
            minCost = cost[i];
        }
        res += minCost * dist[i];
    }
    cout << res << "\n";
    return 0;
}
