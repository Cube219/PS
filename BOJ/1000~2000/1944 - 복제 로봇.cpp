#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <queue>
using namespace std;

using ll = long long int;

int n, m;
char map[52][52];
pair<int, int> pos[301];
int posNum;
int idx[5001];
struct Node
{
    int x;
    int y;
    int cost;
};
queue<Node> q;
struct Edge
{
    int a;
    int b;
    ll cost;
};
vector<Edge> edges;
bool isVisited[52][52];
int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { 1, 0, -1, 0 };

int p[301];

int res;
int cnt;

void search(int x, int y)
{
    while(q.empty() == false) q.pop();
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            isVisited[i][j] = false;
        }
    }

    int myIdx = idx[x * 100 + y];
    q.push({ x, y, 0 });
    isVisited[x][y] = true;
    while(q.empty() == false) {
        int cx = q.front().x;
        int cy = q.front().y;
        int cc = q.front().cost;
        q.pop();

        if(map[cx][cy] == 'S' || map[cx][cy] == 'K') {
            int otherIdx = idx[cx * 100 + cy];
            if(myIdx != otherIdx) {
                edges.push_back({ myIdx, otherIdx, cc });
            }
        }
        cc++;

        for(int i = 0; i < 4; ++i) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];
            if(isVisited[nx][ny] == true || map[nx][ny] == '1') continue;

            isVisited[nx][ny] = true;
            q.push({ nx, ny, cc });
        }
    }
}

int find(int a)
{
    if(p[a] == a) return a;

    int res = find(p[a]);
    p[a] = res;
    return res;
}

void uni(int a, int b)
{
    int ar = find(a);
    int br = find(b);

    if(ar == br) return;

    p[ar] = br;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < n; ++i) {
        cin >> map[i];

        for(int j = 0; j < n; ++j) {
            if(map[i][j] == 'S' || map[i][j] == 'K') {
                pos[posNum].first = i;
                pos[posNum].second = j;
                idx[i * 100 + j] = posNum;
                posNum++;
            }
        }
    }

    for(int i = 0; i < posNum; ++i) {
        search(pos[i].first, pos[i].second);
        p[i] = i;
    }

    sort(edges.begin(), edges.end(), [](const Edge& l, const Edge& r) { return l.cost < r.cost; });

    for(int i = 0; i < edges.size(); ++i) {
        int a = edges[i].a;
        int b = edges[i].b;
        int cost = edges[i].cost;

        int ar = find(a);
        int br = find(b);
        if(ar == br) continue;

        res += cost;
        uni(ar, br);
        cnt++;

        if(cnt == posNum - 1) break;
    }

    if(cnt != posNum - 1) cout << "-1";
    else cout << res;

    return 0;
}
