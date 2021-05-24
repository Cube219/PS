#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <queue>
using namespace std;

using ll = long long int;
constexpr int INF = 987654321;

struct QNode
{
    int xpos;
    int num;
    vector<int> map;
};

int n, d, stx, edx;
vector<int> stmap, edmap;
int dx[] = { 0, 1, 0, -1 };
int dy[] = { 1, 0, -1, 0 };

pair<int, int> getxy(int pos)
{
    return { pos / n, pos % n };
}
int getpos(int x, int y)
{
    return x * n + y;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while(1) {
        string str;
        cin >> str >> n >> d;
        if(cin.eof() == true) break;

        stmap.resize(n * n);
        edmap.resize(n * n);
        for(int i = 0; i < n * n; ++i) {
            cin >> str;
            int num = 0;
            if(str[0] != 'X') num = stoi(str);
            else stx = i;
            stmap[i] = num;
        }
        for(int i = 0; i < n * n; ++i) {
            cin >> str;
            int num = 0;
            if(str[0] != 'X') num = stoi(str);
            else edx = i;
            edmap[i] = num;
        }
        cin >> str;

        map<vector<int>, int> mp;
        queue<QNode> q;
        q.push({ stx, 0, stmap });
        while(q.empty() == false) {
            QNode cur = q.front();
            q.pop();
            if(mp.find(cur.map) != mp.end()) continue;

            mp.insert({ cur.map, cur.num });
            if(cur.num == d / 2) continue;

            auto [x, y] = getxy(cur.xpos);
            for(int i = 0; i < 4; ++i) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if(nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
                int npos = getpos(nx, ny);
                swap(cur.map[cur.xpos], cur.map[npos]);
                q.push({ npos, cur.num + 1, cur.map });
                swap(cur.map[cur.xpos], cur.map[npos]);
            }
        }
        while(q.empty() == false) q.pop();

        int res = INF;
        q.push({ edx, 0, edmap });
        while(q.empty() == false) {
            QNode cur = q.front();
            q.pop();
            auto it = mp.find(cur.map);
            if(it != mp.end()) {
                res = min(res, it->second + cur.num);
            }
            if(cur.num == (d + 1) / 2) continue;

            auto [x, y] = getxy(cur.xpos);
            for(int i = 0; i < 4; ++i) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if(nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
                int npos = getpos(nx, ny);
                swap(cur.map[cur.xpos], cur.map[npos]);
                q.push({ npos, cur.num + 1, cur.map });
                swap(cur.map[cur.xpos], cur.map[npos]);
            }
        }

        if(res == INF || res > d) {
            cout << "NOT SOLVABLE WITHIN " << d << " MOVES\n\n";
        } else {
            cout << "SOLVABLE WITHIN " << res << " MOVES\n\n";
        }
    }

    return 0;
}
