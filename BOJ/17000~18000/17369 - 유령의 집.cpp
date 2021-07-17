#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

using ll = long long int;

int n, m, k, q;
pair<ll, int> dp[300005][4];
pair<ll, int> upres[300005], downres[300005], leftres[300005], rightres[300005];
char mp[300005];
vector<pair<int, int>> row[300005], col[300005];
constexpr int udir = 0, ddir = 1, ldir = 2, rdir = 3;
int dx[] = { -1, 1, 0, 0 }, dy[] = { 0, 0, -1, 1 };

pair<ll, int> get(int x, int y, int node, int dir)
{
    if(node != -1 && dp[node][dir].first != -1) return dp[node][dir];

    // 끝점인 경우
    int rowidx = lower_bound(row[x].begin(), row[x].end(), y, [](auto& node, int v) { return node.first < v; }) - row[x].begin();
    int colidx = lower_bound(col[y].begin(), col[y].end(), x, [](auto& node, int v) { return node.first < v; }) - col[y].begin();

    if(x == 0) colidx = -1;
    if(y == 0) rowidx = -1;

    pair<ll, int> res = { 0, 0 };
    while(1) {
        rowidx += dy[dir];
        colidx += dx[dir];

        if(dir == udir || dir == ddir) { // 상하
            if(colidx < 0 || colidx >= col[y].size()) break;

            int curnode = col[y][colidx].second;
            int cx = col[y][colidx].first;
            int cy = y;
            ll len = abs(x - cx);

            if(mp[curnode] == '!') { // 유령
                res.second++;
                res.first += len;
            } else {
                int nxtdir;
                if(mp[curnode] == '/') {
                    if(dir == udir) {
                        nxtdir = rdir;
                    } else {
                        nxtdir = ldir;
                    }
                } else {
                    if(dir == udir) {
                        nxtdir = ldir;
                    } else {
                        nxtdir = rdir;
                    }
                }
                pair<ll, int> r = get(cx, cy, curnode, nxtdir);
                res.second += r.second;
                res.first += len * r.second + r.first;
                break;
            }
        } else { // 좌우
            if(rowidx < 0 || rowidx >= row[x].size()) break;

            int curnode = row[x][rowidx].second;
            int cx = x;
            int cy = row[x][rowidx].first;
            ll len = abs(y - cy);

            if(mp[curnode] == '!') { // 유령
                res.second++;
                res.first += len;
            } else {
                int nxtdir;
                if(mp[curnode] == '/') {
                    if(dir == ldir) nxtdir = ddir;
                    else nxtdir = udir;
                } else {
                    if(dir == ldir) nxtdir = udir;
                    else nxtdir = ddir;
                }
                pair<ll, int> r = get(cx, cy, curnode, nxtdir);
                res.second += r.second;
                res.first += len * r.second + r.first;
                break;
            }
        }
    }

    if(node != -1) dp[node][dir] = res;
    return res;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // o:유령  1:/  2:
    cin >> n >> m >> k >> q;
    for(int i = 0; i < k; ++i) {
        int x, y;
        char ch;
        cin >> x >> y >> ch;
        mp[i] = ch;
        row[x].push_back({ y, i });
        col[y].push_back({ x, i });

        for(int j = 0; j < 4; ++j) {
            dp[i][j].first = -1;
        }
    }
    for(int i = 1; i <= n; ++i) {
        sort(row[i].begin(), row[i].end());
        leftres[i].first = -1;
        rightres[i].first = -1;
    }
    for(int i = 1; i <= m; ++i) {
        sort(col[i].begin(), col[i].end());
        upres[i].first = -1;
        downres[i].first = -1;
    }

    for(int i = 0; i < q; ++i) {
        string str;
        cin >> str;
        int v = 0;
        for(int j = 1; j < str.size(); ++j) {
            v *= 10;
            v += str[j] - '0';
        }
        if(str[0] == 'U') {
            if(upres[v].first == -1) upres[v] = get(0, v, -1, ddir);
            cout << upres[v].second << " " << upres[v].first << "\n";
        } else if(str[0] == 'D') {
            if(downres[v].first == -1) downres[v] = get(n + 1, v, -1, udir);
            cout << downres[v].second << " " << downres[v].first << "\n";
        } else if(str[0] == 'L') {
            if(leftres[v].first == -1) leftres[v] = get(v, 0, -1, rdir);
            cout << leftres[v].second << " " << leftres[v].first << "\n";
        } else { // R
            if(rightres[v].first == -1) rightres[v] = get(v, m + 1, -1, ldir);
            cout << rightres[v].second << " " << rightres[v].first << "\n";
        }
    }

    return 0;
}
