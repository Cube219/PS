#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

using ll = long long int;

int n, m;
vector<int> g[1001][30];
int d[1001][1001];
bool g2[1001][1001];

int res;
constexpr int INF = 987654321;

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
        char c;
        cin >> a >> b >> c;
        g[a][c - 'a'].push_back(b);
        g[b][c - 'a'].push_back(a);
        g2[a][b] = true;
        g2[b][a] = true;
    }
    for(int i = 0; i <= n; ++i) {
        for(int j = 0; j <= n; ++j) {
            d[i][j] = INF;
        }
    }
    res = INF;

    queue<pair<int, int>> q;
    q.push({ 1, n });
    d[1][n] = 0;
    while(q.empty() == false) {
        int s = q.front().first;
        int e = q.front().second;
        q.pop();

        if(s == e) {
            res = min(res, d[s][e]);
        } else if(g2[s][e] == true) {
            res = min(res, d[s][e] + 1);
        }

        for(int i = 0; i <= 'z' - 'a'; ++i) {
            for(int ns : g[s][i]) {
                for(int ne : g[e][i]) {
                    if(d[ns][ne] > d[s][e] + 2) {
                        d[ns][ne] = d[s][e] + 2;
                        q.push({ ns, ne });
                    }
                }
            }

        }
    }

    if(res == INF) res = -1;
    cout << res;

    return 0;
}
