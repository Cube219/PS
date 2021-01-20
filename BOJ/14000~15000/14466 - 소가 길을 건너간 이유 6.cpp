#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

using ll = long long int;

int n, k, r;
int cow[102][102];
int cowX[10002], cowY[10002];
int g[102][102];
// 1-left 2-down 4-right 8-up
const int cleft = 1;
const int cdown = 2;
const int cright = 4;
const int cup = 8;
int res;
int cnt;
bool isVisit[102][102];
queue<pair<int, int>> q;

inline bool isValid(int x, int y)
{
    if(isVisit[x][y] == true) return false;
    if(x < 1 || x > n || y < 1 || y > n) return false;

    return true;
}

void bfs(int x, int y)
{
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            isVisit[i][j] = false;
        }
    }

    cnt = 0;
    q.push({ x, y });
    isVisit[x][y] = true;
    while(q.empty() == false) {
        auto qq = q.front();
        q.pop();

        int cx = qq.first;
        int cy = qq.second;
        // cout << cx << " " << cy << endl;

        if(cow[cx][cy] == 1) cnt++;

        // left
        if((g[cx][cy] & cleft) == 0 && isValid(cx, cy - 1)) {
            q.push({ cx, cy - 1 });
            isVisit[cx][cy - 1] = true;
        }

        // down
        if((g[cx][cy] & cdown) == 0 && isValid(cx + 1, cy)) {
            q.push({ cx + 1, cy });
            isVisit[cx + 1][cy] = true;
        }

        // right
        if((g[cx][cy] & cright) == 0 && isValid(cx, cy + 1)) {
            q.push({ cx, cy + 1 });
            isVisit[cx][cy + 1] = true;
        }

        // up
        if((g[cx][cy] & cup) == 0 && isValid(cx - 1, cy)) {
            q.push({ cx - 1, cy });
            isVisit[cx - 1][cy] = true;
        }
    }

    res += k - cnt;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k >> r;
    for(int i = 0; i < r; i++) {
        int x1, x2, y1, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if(x1 == x2) {
            if(y1 < y2) {
                g[x1][y1] |= cright;
                g[x2][y2] |= cleft;
            } else {
                g[x1][y1] |= cleft;
                g[x2][y2] |= cright;
            }
        } else {
            if(x1 < x2) {
                g[x1][y1] |= cdown;
                g[x2][y2] |= cup;
            } else {
                g[x1][y1] |= cup;
                g[x2][y2] |= cdown;
            }
        }
    }
    for(int i = 0; i < k; i++) {
        int x, y;
        cin >> x >> y;
        cow[x][y] = 1;
        cowX[i] = x;
        cowY[i] = y;
    }

    for(int i = 0; i < k; i++) {
        cnt = 0;
        bfs(cowX[i], cowY[i]);
    }

    cout << res / 2;

    return 0;
}
