#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, m, lNum;
vector<int> g[10001];
bool blockh[10001], blockv[10001];
int d[10001];
bool visit[10001];

void initGraph()
{
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            int cur = i * m + j;

            int nxt = cur + 1;
            if(blockh[cur] == false) {
                if(j < m - 1) {
                    if((i + j) % 2 == 0) {
                        g[cur].push_back(nxt);
                    } else {
                        g[nxt].push_back(cur);
                    }
                }
            }

            nxt = cur + m;
            if(blockv[cur] == false) {
                if(nxt < n * m) {
                    if((i + j) % 2 == 0) {
                        g[cur].push_back(nxt);
                    } else {
                        g[nxt].push_back(cur);
                    }
                }
            }
        }
    }

    for(int i = 0; i < n * m; ++i) {
        d[i] = -1;
    }
}

bool dfs(int cur)
{
    visit[cur] = true;
    for(int nxt : g[cur]) {
        if(d[nxt] == -1 || (visit[d[nxt]] == false && dfs(d[nxt]))) {
            d[nxt] = cur;
            return true;
        }
    }

    return false;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> lNum;
    for(int i = 0; i < lNum; ++i) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        if(a > b) swap(a, b);

        if(a + 1 == b) blockh[a] = true;
        else blockv[a] = true;
    }

    initGraph();

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if((i + j) % 2 == 1) continue;

            if(d[i * m + j] == -1) {
                for(int k = 0; k < n * m; ++k) {
                    visit[k] = false;
                }
                dfs(i * m + j);
            }
        }
    }

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            int num = i * m + j;
            if((i + j) % 2 == 1) {
                cout << d[num] + 1 << " " << num + 1 << "\n";
            }
        }
    }

    return 0;
}
