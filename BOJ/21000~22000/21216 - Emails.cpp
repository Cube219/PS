#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

using ll = long long int;
constexpr int INF = 987654321;

int n, m;
vector<int> g[100001];
int d[100001];

pair<int, int> bfs(int st)
{
    for(int i = 0; i < n; ++i) {
        d[i] = INF;
    }
    queue<pair<int, int>> q;
    q.push({ st, 0 });
    d[st] = 0;
    while(q.empty() == false) {
        auto cur = q.front();
        q.pop();

        for(int nxt : g[cur.first]) {
            if(d[nxt] == INF) {
                d[nxt] = d[cur.first] + 1;
                q.push({ nxt, d[nxt] });
            }
        }
    }
    int maxv = 0, maxidx = 0;
    for(int i = 0; i < n; ++i) {
        if(d[i] == INF) {
            return { -1, -1 };
        }
        if(d[i] > maxv) {
            maxv = d[i];
            maxidx = i;
        }
    }
    return { maxv, maxidx };
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    auto r1 = bfs(0);
    if(r1.first == -1) {
        cout << "-1";
        return 0;
    }
    auto r2 = bfs(r1.second);

    ll len = r2.first;
    if(len == 1) cout << "0";
    else {
        ll cur = 1;
        for(int i = 1; i < n; ++i) {
            if(cur * 2 >= len) {
                cout << i;
                break;
            }
            cur *= 2;
        }
    }

    return 0;
}
