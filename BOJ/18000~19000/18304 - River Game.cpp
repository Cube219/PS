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

struct Place
{
    vector<pair<int, int>> pos;
    vector<int> dp;
    int id;
};

int n;
char map[12][12];
bool comp[12][12];
bool place[12][12];
int idx[12][12];
int pidx[12][12];
int dx[] = { 0, 1, 0, -1 }, dy[] = { 1, 0, -1, 0 };
vector<Place> d;

void p(int x, int y)
{
    queue<pair<int, int>> q;
    q.push({ x, y });
    comp[x][y] = true;
    while(q.empty() == false) {
        auto [x, y] = q.front();
        q.pop();

        for(int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if(nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
            if(comp[nx][ny]) continue;
            if(map[nx][ny] == '*') {
                comp[nx][ny] = true;
                q.push({ nx, ny });
            } else if(map[nx][ny] == '.') {
                place[nx][ny] = true;
            }
        }
    }

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            if(place[i][j] == false) continue;

            d.push_back(Place());
            d.back().id = d.size();

            q.push({ i, j });
            place[i][j] = false;
            while(q.empty() == false) {
                auto [x, y] = q.front();
                q.pop();

                d.back().pos.push_back({ x, y });
                idx[x][y] = d.back().pos.size() - 1;
                pidx[x][y] = d.size();

                for(int k = 0; k < 4; ++k) {
                    int nx = x + dx[k];
                    int ny = y + dy[k];
                    if(nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
                    if(place[nx][ny] == false) continue;

                    place[nx][ny] = false;
                    q.push({ nx, ny });
                }
            }

            int sz = d.back().pos.size();
            d.back().dp.resize(1 << sz, -1);
        }
    }
}

int p2(Place& cur, int mask)
{
    if(cur.dp[mask] != -1) return cur.dp[mask];

    vector<bool> has(cur.pos.size() + 5, false);
    for(int i = 0; i < cur.pos.size(); ++i) {
        int bit = 1 << i;
        if((bit & mask) > 0) continue;

        int x = cur.pos[i].first;
        int y = cur.pos[i].second;

        bool pos = true;
        for(int j = 0; j < 4; ++j) {
            int nx = x + dx[j];
            int ny = y + dy[j];
            if(nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
            if(pidx[nx][ny] != cur.id) continue;

            int nxidx = idx[nx][ny];
            int nxbit = 1 << nxidx;
            if((nxbit & mask) > 0) {
                pos = false;
                break;
            }
        }

        if(pos == true) {
            int v = p2(cur, mask | bit);
            has[v] = true;
        }
    }

    for(int i = 0; i < has.size(); ++i) {
        if(has[i] == false) {
            cur.dp[mask] = i;
            break;
        }
    }
    return cur.dp[mask];
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> map[i];
    }

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            if(comp[i][j] == true || map[i][j] != '*') continue;
            p(i, j);
        }
    }

    int res = 0;
    for(auto& v : d) {
        res ^= p2(v, 0);
    }

    if(res == 0) cout << "Second player will win";
    else cout << "First player will win";

    return 0;
}
