#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <set>
#include <limits>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

// 튜플: (profit, id, revenue, dest)
//  -> priority_queue는 첫 번째 요소가 큰 순으로 최대힙 구성
using tiiii = tuple<int, int, int, int>;

const int INF = 1e9;
int N, M, Q;
int start = 0;

// 그래프: G[u] = { (v, w), ... }
vector<vector<pii>> G;

// 커스텀 비교자
struct cmp {
    bool operator()(const tiiii &a, const tiiii &b) const {
        auto [aProfit, aId, aRev, aDest] = a;
        auto [bProfit, bId, bRev, bDest] = b;
        if (aProfit != bProfit) {
            return aProfit < bProfit; // profit 큰 순
        }
        return aId > bId;            // id 작은 순
    }
};

priority_queue<tiiii, vector<tiiii>, cmp> I;

// 출발지별 최단거리 캐싱
// distDic[s][v] = s->v 최단거리
unordered_map<int, vector<int>> distDic;

// 현재 살아 있는 상품들의 id를 모아둠
set<int> idSet;

// 다익스트라
vector<int> dijkstra(int st) {
    vector<int> dist(N+1, INF);
    priority_queue<pii, vector<pii>, greater<pii>> pq; // (비용, 노드)

    dist[st] = 0;
    pq.emplace(0, st);

    while (!pq.empty()) {
        auto [cost, v] = pq.top();
        pq.pop();
        if (dist[v] < cost) continue;

        for (auto [nv, nw] : G[v]) {
            int ncost = cost + nw;
            if (ncost < dist[nv]) {
                dist[nv] = ncost;
                pq.emplace(ncost, nv);
            }
        }
    }
    return dist;
}

// (100) 그래프 생성 및 간선 입력
// N, M 입력받은 뒤, M개의 (v, u, w) 간선 반영
void comm100(int v, int u, int w) {
    if(v != u){
        G[v].emplace_back(u, w);
        G[u].emplace_back(v, w);
    }
}

// (200) 여행 상품 등록
// profit = (revenue - 최단거리)
// 최대 이익 상품부터 top에 오도록 (profit, id, revenue, dest) push
void comm200(int id, int revn, int dest) {
    // 아직 start에 대한 최단거리 미캐싱 시 다익스트라
    if (distDic.find(start) == distDic.end()) {
        distDic[start] = dijkstra(start);
    }
    int cost = distDic[start][dest];
    int profit = revn - cost; // 이익

    I.emplace(profit, id, revn, dest);
    idSet.insert(id);
}

// (300) 여행 상품 취소
// 실제 큐에서 빼지는 않고, idSet에서 제거만 => lazy removal
void comm300(int id) {
    idSet.erase(id);
}

// (400) 최적의 상품 판매
// - 큐 top 상품 중 idSet에 없는(취소된) 상품은 제거
// - profit <= 0 이면 판매 불가(-1 출력), 다시 push
// - profit > 0이면 판매
void comm400() {
    // 우선 top에서 취소된 상품들은 제거
    while (!I.empty()) {
        auto [profit, idx, revenue, dest] = I.top();
        if (idSet.find(idx) != idSet.end()) break; 
        I.pop();
    }

    // 가장 이익이 큰 상품 확인
    if (!I.empty()) {
        auto [profit, idx, revenue, dest] = I.top();
        I.pop();

        if (profit < 0) {
            cout << -1 << "\n";
            I.emplace(profit, idx, revenue, dest);
        } else {
            cout << idx << "\n";
            idSet.erase(idx);
        }
    } else {
        cout << -1 << "\n";
    }
}

// (500) 출발지 변경
// - 새 출발지에 대해 다익스트라 실행
// - 큐에 있는 모든 상품의 profit 재계산
void comm500(int newSt) {
    start = newSt;
    distDic.clear();
    distDic[start] = dijkstra(start);

    vector<tiiii> tmp;
    // 모든 상품을 우선 pop해서 이익 갱신
    while (!I.empty()) {
        auto [profit, idx, revenue, dest] = I.top();
        I.pop();
        if (idSet.find(idx) == idSet.end()) {
            continue;
        }
        int cost = distDic[start][dest];
        int newProfit = revenue - cost;
        tmp.emplace_back(newProfit, idx, revenue, dest);
    }
    for (auto &item : tmp) {
        I.push(item);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> Q;
    while (Q--) {
        int comm;
        cin >> comm;
        if (comm == 100) {
            cin >> N >> M;
            G.assign(N+1, vector<pii>());
            // 새 그래프 구성
            for (int i = 0; i < M; i++) {
                int v, u, w;
                cin >> v >> u >> w;
                comm100(v, u, w);
            }
        }
        else if (comm == 200) {
            int id, revn, dest;
            cin >> id >> revn >> dest;
            comm200(id, revn, dest);
        }
        else if (comm == 300) {
            int id;
            cin >> id;
            comm300(id);
        }
        else if (comm == 400) {
            comm400();
        }
        else if (comm == 500) {
            int newSt;
            cin >> newSt;
            comm500(newSt);
        }
    }
    return 0;
}
