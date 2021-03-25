#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

using ll = long long int;

int r, c;
char map[52][52];
int info[52][52];
int cNum, pNum;

vector<pair<int, int>> g[3000];
int a[3000], b[3000];
bool isComp[3000];
bool bp(int cur, int k)
{
    isComp[cur] = true;
    for(auto& nx : g[cur]) {
        int nxt = nx.first;
        int cost = nx.second;
        if(cost > k) continue;

        if(b[nxt] == 0) {
            a[cur] = nxt;
            b[nxt] = cur;
            return true;
        } else if(isComp[b[nxt]] == false) {
            bool f = bp(b[nxt], k);
            if(f == true) {
                a[cur] = nxt;
                b[nxt] = cur;
                return true;
            }
        }
    }
    return false;
}

bool visit[51][51];
int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { 1, 0, -1, 0 };
void addEdge(int x, int y)
{
    for(int i = 0; i < r; ++i) {
        for(int j = 0; j < c; ++j) {
            visit[i][j] = false;
        }
    }

    queue<pair<int, int>> q;
    queue<int> cntq;
    q.push({ x, y });
    cntq.push(0);
    while(q.empty() == false) {
        int cx = q.front().first;
        int cy = q.front().second;
        int cnt = cntq.front();
        q.pop();
        cntq.pop();

        if(visit[cx][cy] == true) continue;
        visit[cx][cy] = true;
        if(map[cx][cy] == 'P') {
            g[info[x][y]].push_back({ info[cx][cy], cnt });
        }

        for(int i = 0; i < 4; ++i) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];

            if(map[nx][ny] == 'X' || visit[nx][ny] == true) continue;
            if(nx < 0 || ny < 0 || nx >= r || ny >= c) continue;

            q.push({ nx, ny });
            cntq.push(cnt + 1);
        }
    }
}

bool ck(int k)
{
    int res = 0;
    for(int i = 1; i <= cNum; ++i) {
        a[i] = 0;
    }
    for(int i = 1; i <= pNum; ++i) {
        b[i] = 0;
    }

    for(int i = 1; i <= cNum; ++i) {
        if(a[i] == 0) {
            for(int j = 1; j <= cNum; ++j) {
                isComp[j] = false;
            }
            if(bp(i, k) == true) res++;
        }
    }
    if(res < cNum) return false;
    return true;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> r >> c;
    for(int i = 0; i < r; ++i) {
        cin >> map[i];
    }

    for(int i = 0; i < r; ++i) {
        for(int j = 0; j < c; ++j) {
            if(map[i][j] == 'C') {
                info[i][j] = ++cNum;
            } else if(map[i][j] == 'P') {
                info[i][j] = ++pNum;
            }
        }
    }

    for(int i = 0; i < r; ++i) {
        for(int j = 0; j < c; ++j) {
            if(map[i][j] == 'C') {
                addEdge(i, j);
            }
        }
    }

    int lv = 0, rv = 2501;
    while(lv + 1 < rv) {
        int m = (lv + rv) / 2;
        if(ck(m) == true) {
            rv = m;
        } else {
            lv = m;
        }
    }
    if(rv == 2501) rv = -1;
    if(cNum == 0) rv = 0;
    cout << rv;

    return 0;
}
