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

int n, m1, m2;
vector<pair<int, ll>> g[1001];
ll dst[1001];
bool inq[1001];
int cycle[1001];

bool spfa()
{
    for(int i = 0; i < n; ++i) {
        dst[i] = INF;
    }

    dst[0] = 0;
    queue<int> q;
    q.push(0);
    while(q.empty() == false) {
        int cur = q.front();
        q.pop();
        inq[cur] = false;
        for(auto& nx : g[cur]) {
            int nxt = nx.first;
            ll cost = nx.second;
            if(dst[nxt] > dst[cur] + cost) {
                dst[nxt] = dst[cur] + cost;
                if(inq[nxt] == false) {
                    q.push(nxt);
                    inq[nxt] = true;
                }
                cycle[nxt]++;
                if(cycle[nxt] > n) {
                    return false;
                }
            }
        }
    }
    return true;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m1 >> m2;
    for(int i = 0; i < m1; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        g[a].push_back({ b, c });
    }
    for(int i = 0; i < m2; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        g[b].push_back({ a, -c });
    }
    for(int i = 0; i < n - 1; ++i) {
        g[i + 1].push_back({ i, 0 });
    }

    bool r = spfa();
    ll res = dst[n - 1];
    if(r == false) res = -1;
    if(res == INF) res = -2;

    cout << res;

    return 0;
}
