#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll INF = 9999999999999999;

struct Node
{
    int x, y, mask;
    ll cost;
};

int n, m;
char map[11][11];
bool visit[11][11][1 << 14];

char rotate(char ch)
{
    if(ch == 'C') return 'D';
    else if(ch == 'D') return 'C';
    return ch;
}

char get(int x, int y, int mask)
{
    char cur = map[x][y];
    int rbit = 1 << (m + x);
    int cbit = 1 << y;
    if((mask & rbit) > 0) cur = rotate(cur);
    if((mask & cbit) > 0) cur = rotate(cur);
    return cur;
}

void addq(int nx, int ny, int nmask, char curch, char acceptch, int curcost, queue<Node>& q)
{
    if(nx < 0 || ny < 0 || nx >= n || ny >= m) return;
    if(visit[nx][ny][nmask] == true) return;

    char nxtch = get(nx, ny, nmask);
    if(curch == 'A' || curch == acceptch) {
        if(nxtch == 'A' || nxtch == acceptch) {
            q.push({ nx, ny, nmask, curcost + 1 });
            visit[nx][ny][nmask] = true;
        }
    }
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < n; ++i) {
        cin >> map[i];
    }

    ll res = INF;
    queue<Node> q;
    q.push({ 0, 0, 0, 0 });
    visit[0][0][0] = true;
    while(q.empty() == false) {
        Node cur = q.front();
        q.pop();

        if(cur.x == n - 1 && cur.y == m - 1) {
            res = min(res, cur.cost);
            break;
        }

        char curch = get(cur.x, cur.y, cur.mask);

        // Up
        addq(cur.x - 1, cur.y, cur.mask, curch, 'C', cur.cost, q);

        // Down
        addq(cur.x + 1, cur.y, cur.mask, curch, 'C', cur.cost, q);

        // Left
        addq(cur.x, cur.y - 1, cur.mask, curch, 'D', cur.cost, q);

        // Right
        addq(cur.x, cur.y + 1, cur.mask, curch, 'D', cur.cost, q);

        // Press
        int nmask = cur.mask;
        int rbit = 1 << (m + cur.x);
        int cbit = 1 << cur.y;
        if((nmask & rbit) == 0) nmask |= rbit;
        else nmask &= ~rbit;
        if((nmask & cbit) == 0) nmask |= cbit;
        else nmask &= ~cbit;

        if(visit[cur.x][cur.y][nmask] == false) {
            visit[cur.x][cur.y][nmask] = true;
            q.push({ cur.x, cur.y, nmask, cur.cost + 1 });
        }
    }

    if(res == INF) res = -1;
    cout << res;

    return 0;
}
