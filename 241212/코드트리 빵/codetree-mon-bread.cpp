#include <iostream>
#include <queue>
using namespace std;
using pii = pair<int, int>;
using pipii = pair<int, pair<int, int>>;

int N, M;
int grid[16][16]; // 0 : 빈 칸, 1 : BC, -1 : 잠긴 칸
pii pos[31]; // 사람의 위치
pii goals[31]; // 목표 편의점 위치
bool arrived[31]= {false, }; // 사람의 편의점 도착 여부
const int MAX = 1e9;
const int dr[4] = {-1, 0, 0, 1};
const int dc[4] = {0, -1, 1, 0};

void init(){ // 사람 위치 초기화
    for(int i=0; i<31; ++i) {
        pos[i] = {16, 16};
    }
}

bool rangeCheck(int r, int c){
    return (0 < r && r <= N && 0 < c && c <= N);
}

// 1. t번 사람이 BC 찾는 함수(BFS)
void findBestBC(int sr, int sc, int idx){
    bool vst[16][16] = {false, };
    int minDist = MAX;
    queue<pipii> Q; // <dist, <r, c>> 순서
    Q.push({0, {sr, sc}});

    while(!Q.empty()){
        pipii tmp = Q.front();
        Q.pop();

        int dist = tmp.first;
        int r = tmp.second.first;
        int c = tmp.second.second;
        vst[r][c] = true;

        for (int i=0; i<4; ++i){
            int nr = r + dr[i];
            int nc = c + dc[i];

            // 범위 체크, 방문 체크
            if(rangeCheck(nr, nc) && grid[nr][nc] != -1 && !vst[nr][nc]){
                if (grid[nr][nc] == 1 && minDist >= dist+1){
                    // 최단 거리로 BC 도착했을 때
                    if (pos[idx].first > nr || (pos[idx].first == nr && pos[idx].second > nc)){
                        pos[idx] = {nr, nc};
                        minDist = dist+1;
                    }
                }
                else if (grid[nr][nc] != 1) Q.push({dist+1, {nr, nc}});
            }
        }
    }
}

// 2. 격자 4방향 중 이동 방향 정하는 함수 (4방향, 상 좌 우 하 순서)
int findDir(int sr, int sc, int gr, int gc){
    bool vst[16][16] = {false, };
    queue<pipii> Q; // <dist, <r, c>> 순서
    Q.push({0, {sr, sc}});

    while(!Q.empty()){
        pipii tmp = Q.front();
        Q.pop();

        int dist = tmp.first;
        int r = tmp.second.first;
        int c = tmp.second.second;
        vst[r][c] = true;

        if(r == gr && c == gc) return dist;

        for (int i=0; i<4; ++i){
            int nr = r + dr[i];
            int nc = c + dc[i];

            // 범위 체크
            if(rangeCheck(nr, nc) && grid[nr][nc] != -1 && !vst[nr][nc]){
                Q.push({dist+1, {nr, nc}});
            }
        }
    }
    return MAX; // 도착 불가능한 경우
}

// 3. 좌표 잠그는 함수
void blockSpace(int r, int c){
    grid[r][c] = -1;
}

bool checkEnd(int maxP){
    for(int i=1; i<=maxP; ++i){
        if(!arrived[i]) return false;
    }
    return true;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;
    for (int i=1; i<=N; ++i){
        for (int j=1; j<=N; ++j) {
            cin >> grid[i][j];
        }
    }

    for (int i=1; i<=M; ++i){
        cin >> goals[i].first >> goals[i].second;
    }

    init();
    int time = 0;
    while(true){
        ++time;

        for(int i=1; i <= M && i < time; ++i){
            // 1. 가고 싶은 편의점 방향 향해서 이동
            if(!arrived[i]){
                int minDist = MAX;
                int minDir = -1;

                for(int d=0; d<4; ++d){
                    int sr = pos[i].first + dr[d];
                    int sc = pos[i].second + dc[d];

                    if(rangeCheck(sr, sc) && grid[sr][sc] != -1){
                        int nowDist = findDir(sr, sc, goals[i].first, goals[i].second);
                        if (minDist > nowDist){
                            minDist = nowDist;
                            minDir = d;
                        }
                    }
                }
                //minDir 만큼 이동, 도착은 나중에 한 번에 처리
                pos[i].first += dr[minDir];
                pos[i].second += dc[minDir];
            }
        }

        // 3. BC 배정
        if(time <= M) findBestBC(goals[time].first, goals[time].second, time);

        // 좌표 잠그기 (도착한 곳, BC 배정한 곳)
        for(int i=1; i<=M; ++i){
            if(pos[i] == goals[i] && !arrived[i]){
                arrived[i] = true;
                blockSpace(pos[i].first, pos[i].second);
            }
        }
        blockSpace(pos[time].first, pos[time].second);
        if(checkEnd(M)) break; // 모두 도착하면 게임 종료
    }
    cout << time;
    return 0;
}